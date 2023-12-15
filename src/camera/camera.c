/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:29:44 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/15 20:11:40 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

t_camera	init_camera(double aspect_ratio, int image_width)
{
	t_camera	this;

	this.aspect_ratio = aspect_ratio;
	this.image_width = image_width;
	this.image_height = (int)(image_width / aspect_ratio);
	if (this.image_height < 1)
		this.image_height = 1;
	this.samples_per_pixel = 10;
	this.center = init_vector(0, 0, 0);

	// Determine viewport dimensions.
	double	focal_len = 1.0;
	double	viewport_h = 2.0;
	double	viewport_w = viewport_h * aspect_ratio;

	// Calculate the vectors across the horizontal and down the verticla viewport edges.
	t_vec3	viewport_u = init_vector(viewport_w, 0, 0);
	t_vec3	viewport_v = init_vector(0, -viewport_h, 0);

	// Calculate the horizontal and vertical delta vectors from pixel to pixel.
	this.pixel_delta_u = scale(viewport_u, 1.0 / this.image_width);
	this.pixel_delta_v = scale(viewport_v, 1.0 / this.image_height);

	t_vec3	viewport_upper_left = init_vector(
			this.center.x - 0, this.center.y - 0,
			this.center.z - focal_len
			);
	viewport_upper_left = subtract(viewport_upper_left, scale(viewport_u, 0.5));
	viewport_upper_left = subtract(viewport_upper_left, scale(viewport_v, 0.5));

	this.pixel00_loc = (t_vec3){
		viewport_upper_left.x + 0.5 * \
			(this.pixel_delta_u.x + this.pixel_delta_v.x),
		viewport_upper_left.y + 0.5 * \
			(this.pixel_delta_u.y + this.pixel_delta_v.y),
		viewport_upper_left.z + 0.5 * \
			(this.pixel_delta_u.z + this.pixel_delta_v.z),
	};
	return (this);
}

t_vec3	get_rgb(double red, double green, double blue)
{
	red *= 255.999;
	green *= 255.999;
	blue *= 255.999;
	return ((t_vec3){red, green, blue});
}

t_vec3	pixel_sample_square(t_camera camera)
{
	double	px;
	double	py;
	t_vec3	res;

	px = -0.5 + ft_random(0.0, 1.0);
	py = -0.5 + ft_random(0.0, 1.0);
	res = scale(camera.pixel_delta_u, px);
	res = add(res, scale(camera.pixel_delta_v, py));
	return (res);
}

t_ray	get_ray(t_camera camera, int i, int j)
{
	t_vec3	pixel_center;
	t_vec3	pixel_sample;
	t_vec3	ray_origin;
	t_vec3	ray_direction;
	t_ray	ray;

	pixel_center = add(camera.pixel00_loc, \
			scale(camera.pixel_delta_u, (double)i));
	pixel_center = add(pixel_center, \
			scale(camera.pixel_delta_v, (double)j));
	pixel_sample = add(pixel_center, pixel_sample_square(camera));
	ray_origin = camera.center;
	ray_direction = subtract(pixel_sample, ray_origin);
	ray = init_ray(ray_origin, ray_direction);
	return (ray);
}

t_vec3	ray_color(t_ray ray, t_obj *objs[])
{
	t_vec3		color;
	t_hit		rec;
	t_interval	interval;
	t_vec3		unit_direction;
	double		a;

	interval = init_interval(0.001, INFINITY);
	if (hit_objs(objs, ray, interval, &rec))
	{
		color = init_vector(rec.normal.x + 1.0, \
				rec.normal.y + 1.0, rec.normal.z + 1.0);
		color = scale(color, 0.5);
	}
	else
	{
		unit_direction = unit(ray.direction);
		a = 0.5 * (unit_direction.y + 1.0);
		color = scale(init_vector(1.0, 1.0, 1.0), 1.0 - a);
		color = add(color, scale(init_vector(0.5, 0.7, 1.0), a));
	}
	return (color);
}
