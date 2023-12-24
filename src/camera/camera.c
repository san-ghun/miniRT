/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:29:44 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/24 10:18:05 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include <math.h>

double		degrees_to_radians(double degrees)
{
	return (degrees * M_PI / 180.0);
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
		.pixel00_loc = init_vector(0, 0, 0),
		.pixel_delta_u = init_vector(0, 0, 0),
		.pixel_delta_v = init_vector(0, 0, 0),
		.u = init_vector(0, 0, 0),
		.v = init_vector(0, 0, 0),
		.w = init_vector(0, 0, 0),
		.defocus_disk_u = init_vector(0, 0, 0),
		.defocus_disk_v = init_vector(0, 0, 0),
	};
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
	this->samples_per_pixel = 10;
	this->max_depth = 10;
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

void	setup_camera(t_camera *this, int vfov, t_vec3 lookfrom, t_vec3 lookat, t_vec3 vup)
{
	this->vfov = vfov;
	this->lookfrom = lookfrom;
	this->lookat = lookat;
	this->vup = vup;
	this->center = this->lookfrom;
	
	// Determine viewport dimensions.
	double	focal_len = vlen_pow(vsubtract(this->lookfrom, this->lookat));
	double	theta = degrees_to_radians(this->vfov);
	double	h = tan(theta / 2);
	// double	viewport_h = 2.0 * h * focal_len;
	double	viewport_h = 2.0 * h * this->focus_dist;
	double	viewport_w = viewport_h * this->aspect_ratio;

	// Calculate the u,v,w unit basis vector for the camera coordinate frame.
	this->w = vunit(vsubtract(this->lookfrom, this->lookat));
	this->u = vunit(vcross(this->vup, this->w));
	this->v = vcross(this->w, this->u);

	// Calculate the vectors across the horizontal and down the verticla viewport edges.
	t_vec3	viewport_u = vscale(this->u, viewport_w);		// Vector across viewport horizontal edge
	t_vec3	viewport_v = vscale(vflip(this->v), viewport_h);	// Vector down viewport vertical edge

	// Calculate the horizontal and vertical delta vectors from pixel to pixel.
	this->pixel_delta_u = vscale(viewport_u, 1.0 / this->image_width);
	this->pixel_delta_v = vscale(viewport_v, 1.0 / this->image_height);

	// t_vec3	viewport_upper_left = vsubtract(this->center, vscale(this->w, focal_len));
	t_vec3	viewport_upper_left = vsubtract(this->center, vscale(this->w, this->focus_dist));
	viewport_upper_left = vsubtract(viewport_upper_left, vscale(viewport_u, 0.5));
	viewport_upper_left = vsubtract(viewport_upper_left, vscale(viewport_v, 0.5));

	this->pixel00_loc = (t_vec3){
		viewport_upper_left.x + 0.5 * \
			(this->pixel_delta_u.x + this->pixel_delta_v.x),
		viewport_upper_left.y + 0.5 * \
			(this->pixel_delta_u.y + this->pixel_delta_v.y),
		viewport_upper_left.z + 0.5 * \
			(this->pixel_delta_u.z + this->pixel_delta_v.z),
	};

	double	defocus_radius = this->focus_dist * tan(degrees_to_radians(this->defocus_angle / 2));
	this->defocus_disk_u = vscale(this->u, defocus_radius);
	this->defocus_disk_v = vscale(this->v, defocus_radius);
	return ;
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
	ret = vadd(vscale(camera->defocus_disk_u, p.x), vscale(camera->defocus_disk_v, p.y));
	ret = vadd(camera->center, ret);
	return (ret);
}

t_ray	get_ray(t_camera *camera, int i, int j)
{
	t_vec3	pixel_center;
	t_vec3	pixel_sample;
	t_vec3	ray_origin;
	t_vec3	ray_direction;
	t_ray	ray;

	pixel_center = vadd(camera->pixel00_loc, \
			vscale(camera->pixel_delta_u, (double)i));
	pixel_center = vadd(pixel_center, \
			vscale(camera->pixel_delta_v, (double)j));
	pixel_sample = vadd(pixel_center, pixel_sample_square(camera));
	ray_origin = defocus_disk_sample(camera);
	if (camera->defocus_angle <= 0)
		ray_origin = camera->center;
	ray_direction = vsubtract(pixel_sample, ray_origin);
	ray = init_ray(ray_origin, ray_direction);
	return (ray);
}

t_vec3	ray_color(t_ray ray, int depth, t_obj *objs[])
{
	t_subrt		rt_al;
	t_vec3		color;
	t_vec3		ambient;
	t_hit		rec;
	double		a;

	rt_al = single_rt()->a;
	if (depth <= 0)
		return (init_vector(0.0, 0.0, 0.0));
	if (hit_objs(objs, ray, init_interval(0.001, INFINITY), &rec))
	{
		ambient.x = rt_al.ratio * rt_al.color.x * 0.001 * rec.mat->albedo.x;
		ambient.y = rt_al.ratio * rt_al.color.y * 0.001 * rec.mat->albedo.y;
		ambient.z = rt_al.ratio * rt_al.color.z * 0.001 * rec.mat->albedo.z;
		if (scatter(&ray, &rec, &color))
			return (vadd(vmult(ray_color(ray, depth - 1, objs), color), vadd(ambient, rec.mat->emit_color)));
		else
			return (vadd(ambient, rec.mat->emit_color));
	}
	else
	{
		// a = 0.5 * (vunit(ray.direction).y + 1.0);
		// color = vscale(init_vector(1.0, 1.0, 1.0), 1.0 - a);
		// color = vadd(color, vscale(init_vector(0.5, 0.7, 1.0), a));
		return (single_cam()->background);
	}
	return (color);
}
