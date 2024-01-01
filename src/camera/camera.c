/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:29:44 by sanghupa          #+#    #+#             */
/*   Updated: 2024/01/01 13:00:16 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include <math.h>

static t_camera	extra_setup(t_camera *this)
{
	this->u = init_vector(0, 0, 0);
	this->v = init_vector(0, 0, 0);
	this->w = init_vector(0, 0, 0);
	this->viewport_u = init_vector(0, 0, 0);
	this->viewport_v = init_vector(0, 0, 0);
	this->pixel_delta_u = init_vector(0, 0, 0);
	this->pixel_delta_v = init_vector(0, 0, 0);
	this->pixel00_loc = init_vector(0, 0, 0);
	this->defocus_disk_u = init_vector(0, 0, 0);
	this->defocus_disk_v = init_vector(0, 0, 0);
	return (*this);
}

t_camera	*single_cam(void)
{
	static t_camera	this;
	static int		is_init;

	if (is_init)
		return (&this);
	this = (t_camera){
		.aspect_ratio = 0.0,
		.image_width = 0,
		.image_height = 0,
		.samples_per_pixel = 0,
		.max_depth = 0,
		.background = init_vector(0, 0, 0),
		.vfov = 0.0,
		.lookfrom = init_vector(0, 0, 0),
		.lookat = init_vector(0, 0, 0),
		.vup = init_vector(0, 0, 0),
		.defocus_angle = 0.0,
		.focus_dist = 0.0,
		.center = init_vector(0, 0, 0),
	};
	this = extra_setup(&this);
	is_init = 1;
	return (&this);
}

t_camera	*init_camera(double aspect_ratio, int image_width)
{
	t_camera	*this;

	this = single_cam();
	this->aspect_ratio = aspect_ratio;
	if (aspect_ratio < 0)
		this->aspect_ratio = 1.0;
	this->image_width = image_width;
	if (image_width < 1)
		this->image_width = 100;
	this->image_height = (int)(this->image_width / this->aspect_ratio);
	if (this->image_height < 1)
		this->image_height = 1;
	this->samples_per_pixel = N_SAMPLE;
	this->max_depth = N_DEPTH;
	this->background = init_vector(1.0, 1.0, 1.0);
	this->vfov = 90;
	this->lookfrom = init_vector(0.0, 0.0, -1.0);
	this->lookat = init_vector(0.0, 0.0, 0.0);
	this->vup = init_vector(0.0, 1.0, 0.0);
	this->defocus_angle = 0;
	this->focus_dist = 10;
	this->center = this->lookfrom;
	return (this);
}

t_vec3	pixel_sample_square(t_camera *camera)
{
	double	px;
	double	py;
	t_vec3	res;

	px = -0.5 + ft_random(0.0, 1.0);
	py = -0.5 + ft_random(0.0, 1.0);
	res = vscale(camera->pixel_delta_u, px);
	res = vadd(res, vscale(camera->pixel_delta_v, py));
	return (res);
}

t_vec3	defocus_disk_sample(t_camera *camera)
{
	t_vec3	p;
	t_vec3	ret;

	p = random_in_unit_disk();
	ret = vadd(vscale(camera->defocus_disk_u, p.x), \
				vscale(camera->defocus_disk_v, p.y));
	ret = vadd(camera->center, ret);
	return (ret);
}

// t_ray	get_ray(t_camera *camera, int i, int j)
// {
// 	t_vec3	pixel_center;
// 	t_vec3	pixel_sample;
// 	t_vec3	ray_origin;
// 	t_vec3	ray_direction;
// 	t_ray	ray;
//
// 	pixel_center = vadd(camera->pixel00_loc, 
// 		vscale(camera->pixel_delta_u, (double)i));
// 	pixel_center = vadd(pixel_center, 
// 		vscale(camera->pixel_delta_v, (double)j));
// 	pixel_sample = vadd(pixel_center, pixel_sample_square(camera));
// 	ray_origin = defocus_disk_sample(camera);
// 	if (camera->defocus_angle <= 0)
// 		ray_origin = camera->center;
// 	ray_direction = vsubtract(pixel_sample, ray_origin);
// 	ray = init_ray(ray_origin, ray_direction);
// 	return (ray);
// }
