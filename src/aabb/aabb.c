/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 23:34:00 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/22 00:09:03 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aabb.h"

t_aabb	init_aabb_itv(t_interval ix, t_interval iy, t_interval iz)
{
	t_aabb	this;

	this = (t_aabb){
		.x = ix,
		.y = iy,
		.z = iz,
	};
	return (this);
}

t_aabb	init_aabb_vec(t_vec3 a, t_vec3 b)
{
	t_aabb	this;

	this = (t_aabb){
		.x = init_interval(fmin(a.x, b.x), fmax(a.x, b.x)),
		.y = init_interval(fmin(a.y, b.y), fmax(a.y, b.y)),
		.z = init_interval(fmin(a.z, b.z), fmax(a.z, b.z)),
	};
	return (this);
}

t_aabb	init_aabb_box(t_aabb box0, t_aabb box1)
{
	t_aabb	this;

	this = (t_aabb){
		.x = init_interval_itv(box0.x, box1.x),
		.y = init_interval_itv(box0.y, box1.y),
		.z = init_interval_itv(box0.z, box1.z),
	};
	return (this);
}

t_interval	aabb_axis(t_aabb box, int n)
{
	if (n == 1)
		return (box.y);
	if (n == 2)
		return (box.z);
	return (box.x);
}

t_bool	aabb_hit(t_aabb box, t_ray ray, t_interval ray_t)
{
	int		i;
	double	t0;
	double	t1;

	i = -1;
	while (++i < 3)
	{
		t0 = fmin((aabb_axis(box, i).min - vec_val(ray.origin, i)) / vec_val(ray.direction, i),
				(aabb_axis(box, i).max - vec_val(ray.origin, i)) / vec_val(ray.direction, i));
		t1 = fmax((aabb_axis(box, i).min - vec_val(ray.origin, i)) / vec_val(ray.direction, i),
				(aabb_axis(box, i).max - vec_val(ray.origin, i)) / vec_val(ray.direction, i));
		ray_t.min = fmax(t0, ray_t.min);
		ray_t.max = fmin(t1, ray_t.max);
		if (ray_t.max <= ray_t.min)
			return (0);
	}
	return (1);
}

t_aabb	aabb_pad(t_aabb box)
{
	t_interval	new_x;
	t_interval	new_y;
	t_interval	new_z;
	
	new_x = expand_interval(box.x, 0.0001);
	if (size_itv(box.x) >= 0.0001)
		new_x = box.x;
	new_y = expand_interval(box.y, 0.0001);
	if (size_itv(box.y) >= 0.0001)
		new_y = box.y;
	new_z = expand_interval(box.z, 0.0001);
	if (size_itv(box.z) >= 0.0001)
		new_z = box.z;
	return (init_aabb_itv(new_x, new_y, new_z));
}
