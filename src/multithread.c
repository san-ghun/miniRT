/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 21:21:20 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/29 17:10:44 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ft_random.h"

void	render_deprecated(t_camera *camera, t_container *container)
{
	int		i;
	int		j;
	int		sample;
	t_ray	ray;
	t_vec3	col_v;
	double	scalev;
	int		color;

	j = 0;
	ft_printf("P3\n%d %d\n255\n", camera->image_width, camera->image_height);
	while (j < camera->image_height)
	{
		i = 0;
		while (i < camera->image_width)
		{
			col_v = init_vector(0.0, 0.0, 0.0);
			sample = 0;
			while (sample < camera->samples_per_pixel)
			{
				ray = get_ray(camera, i, j);
				col_v = vadd(col_v, ray_color(ray, camera->max_depth, single_rsc()->objs));
				sample++;
			}
			scalev = 1.0 / camera->samples_per_pixel;
			col_v = vscale(col_v, scalev);
			col_v = get_rgb(col_v.x, col_v.y, col_v.z);
			write_color(col_v);
			color = get_trgb(0, (int)col_v.x, (int)col_v.y, (int)col_v.z);
			put_pixel_data(container, i, j, color);
			i++;
		}
		j++;
	}
}

static t_ray	get_ray_thread(t_thread *pth, t_camera *camera, double i, double j)
{
	t_vec3	pixel_center;
	t_vec3	pixel_sample;
	t_vec3	ray_origin;
	t_vec3	ray_direction;
	t_ray	ray;

	i = pth->id * camera->image_width / N_THREAD + i;
	// i = (i + ft_randdouble()) / (double)(camera->image_width - 1);
	// j = (j + ft_randdouble()) / (double)(camera->image_height - 1);
	pixel_center = vadd(camera->pixel00_loc, \
			vscale(camera->pixel_delta_u, i));
	pixel_center = vadd(pixel_center, \
			vscale(camera->pixel_delta_v, j));
	pixel_sample = vadd(pixel_center, pixel_sample_square(camera));
	ray_origin = defocus_disk_sample(camera);
	if (camera->defocus_angle <= 0)
		ray_origin = camera->center;
	ray_direction = vsubtract(pixel_sample, ray_origin);
	ray = init_ray(ray_origin, vunit(ray_direction));
	// ray_direction = vunit(vsubtract(pixel_center, camera->center));
	// ray = init_ray(camera->center, ray_direction);
	return (ray);
}

static void	write_pixel_data(t_thread *pth, int x, int y, int color)
{
	t_container	*cont;
	t_mux		*lock;
	char		*dst;
	int			i;

	cont = single_vars()->container;
	lock = single_rsc()->lock;
	if (x >= 0 && y >= 0 && x < cont->w && y < cont->h)
	{
		dst = cont->addr + \
			(y * cont->line_length + (x + pth->id * cont->w / N_THREAD) * (cont->bits_per_pixel / 8));
		pthread_mutex_lock(lock);
		*(unsigned int *)dst = color;
		pthread_mutex_unlock(lock);
	}
	// dst = cont->addr + \
	// 	(y * cont->line_length + (x + pth->id * cont->w / N_THREAD) * (cont->bits_per_pixel / 8));
	// pthread_mutex_lock(lock);
	// *(unsigned int *)dst = color;
	// pthread_mutex_unlock(lock);
}

static void	*thread_col_calc(void *pth)
{
	int			x;
	int			y;
	int			sample;
	t_container	*container;
	t_camera	*camera;
	t_ray		ray;
	t_vec3		col_v;
	double		scalev;
	int			color;

	container = single_vars()->container;
	camera = single_cam();

	y = -1;
	while (++y < camera->image_height)
	{
		x = -1;
		while (++x < camera->image_width / N_THREAD)
		{
			col_v = init_vector(0.0, 0.0, 0.0);
			sample = -1;
			while (++sample < camera->samples_per_pixel)
			{
				ray = get_ray_thread((t_thread *)pth, camera, x, y);
				col_v = vadd(col_v, ray_color(ray, camera->max_depth, single_rsc()->objs));
			}
			scalev = 1.0 / ((double)camera->samples_per_pixel);
			col_v = vscale(col_v, scalev);
			col_v = get_rgb(col_v.x, col_v.y, col_v.z);
			color = get_trgb(0, (int)col_v.x, (int)col_v.y, (int)col_v.z);
			write_pixel_data((t_thread *)pth, x, y, color);
		}
	}
	return (NULL);
}

void	render(t_camera *camera, t_container *container)
{
	t_resource	*rsc;
	int			i;

	rsc = single_rsc();
	i = -1;
	while (++i < N_THREAD)
		pthread_create(rsc->pths[i]->pth, NULL, thread_col_calc, (void *)rsc->pths[i]);
	i = -1;
	while (++i < N_THREAD)
		pthread_join(*(rsc->pths[i]->pth), NULL);
}
