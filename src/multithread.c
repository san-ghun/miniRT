/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 21:21:20 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/30 00:41:15 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ft_random.h"

static t_ray	get_ray_thread(t_thread *pth, \
								t_camera *camera, double i, double j)
{
	t_vec3	pixel_center;
	t_vec3	pixel_sample;
	t_vec3	ray_origin;
	t_vec3	ray_direction;
	t_ray	ray;

	i = pth->id * camera->image_width / N_THREAD + i;
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
	return (ray);
}

static int	process_color(t_vec3 col_v, t_camera *camera)
{
	double		scalev;
	int			color;

	color = 0;
	scalev = 1.0 / ((double)camera->samples_per_pixel);
	col_v = vscale(col_v, scalev);
	col_v = get_rgb(col_v.x, col_v.y, col_v.z);
	color = get_trgb(0, (int)col_v.x, (int)col_v.y, (int)col_v.z);
	return (color);
}

static void	write_pixel_data(t_thread *pth, int x, int y, int color)
{
	t_container	*cont;
	t_mux		*lock;
	char		*dst;

	cont = single_vars()->container;
	lock = single_rsc()->lock;
	if (x >= 0 && y >= 0 && x < cont->w && y < cont->h)
	{
		dst = cont->addr + \
			(y * cont->line_length + \
			(x + pth->id * cont->w / N_THREAD) * \
			(cont->bits_per_pixel / 8));
		pthread_mutex_lock(lock);
		*(unsigned int *)dst = color;
		pthread_mutex_unlock(lock);
	}
}

static void	*thread_col_calc(void *pth)
{
	int			x;
	int			y;
	int			sample;
	t_camera	*camera;
	t_vec3		col_v;

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
				col_v = vadd(col_v, \
					ray_color(get_ray_thread((t_thread *)pth, camera, x, y), \
						camera->max_depth, single_rsc()->objs));
			write_pixel_data((t_thread *)pth, x, y, \
				process_color(col_v, camera));
		}
	}
	return (NULL);
}

void	render(void)
{
	t_resource	*rsc;
	int			i;

	rsc = single_rsc();
	i = -1;
	while (++i < N_THREAD)
		pthread_create(rsc->pths[i]->pth, NULL, \
			thread_col_calc, (void *)rsc->pths[i]);
	i = -1;
	while (++i < N_THREAD)
		pthread_join(*(rsc->pths[i]->pth), NULL);
}
