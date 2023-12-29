/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 18:34:37 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/29 19:58:53 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include <math.h>
#include <stdio.h>

t_bool	in_shadow(t_ray ray, double lim, t_obj *objs[])
{
	int	i;

	i = -1;
	while (objs[++i] != NULL)
	{
		if (objs[i]->type == SPHERE && interfere_sp((void *)objs[i]->data, ray, lim))
			return (1);
		else if (objs[i]->type == PLANE && interfere_pl((void *)objs[i]->data, ray, lim))
			return (1);
		else if (objs[i]->type == RECTANGLE && interfere_re((void *)objs[i]->data, ray, lim))
			return (1);
		else if (objs[i]->type == CYLINDER && interfere_cy((void *)objs[i]->data, ray, lim))
			return (1);
	}
	return (0);
}

t_vec3	ray_light(t_hit *rec, t_obj *objs[])
{
	t_subrt	*light;
	t_vec3	light_direction;
	double	radius_squared;
	double	distance;
	t_ray	ray;
	double	cos_theta;
	double	brightness;
	t_vec3	color;

	color = (t_vec3){0, 0, 0};
	light = single_rt()->l;
	light_direction = vsubtract(light->point, rec->point);
	radius_squared = vlen_pow(light_direction);
	distance = sqrt(radius_squared);
	ray = init_ray(vadd(rec->point, vscale(rec->normal, 1e-4)), light_direction);
	if (in_shadow(ray, distance, objs))
		return (color);
	light_direction = vscale(light_direction, 1 / sqrt(radius_squared));
	cos_theta = fmax(0.0, vdot(rec->normal, light_direction));
	// if (cos_theta < cos(10.0 / 2))
	// 	return (color);
	brightness = light->ratio * 1;
	light->vector2 = vscale(light->color, brightness);
	color.x = rec->mat->albedo.x * 5.0 / (light->vector2.x + light->vector2.x * 0.1 * distance + light->vector2.x * 0.01 * distance * distance);
	color.y = rec->mat->albedo.y * 5.0 / (light->vector2.y + light->vector2.y * 0.1 * distance + light->vector2.y * 0.01 * distance * distance);
	color.z = rec->mat->albedo.z * 5.0 / (light->vector2.z + light->vector2.z * 0.1 * distance + light->vector2.z * 0.01 * distance * distance);
	// color.x = rec->mat->albedo.x * 5 / M_PI * light->vector2.x;
	// color.y = rec->mat->albedo.y * 5 / M_PI * light->vector2.y;
	// color.z = rec->mat->albedo.z * 5 / M_PI * light->vector2.z;

	return (vscale(color, cos_theta));
}

t_vec3	ray_color(t_ray ray, int depth, t_obj *objs[])
{
	t_subrt		*rt_al;
	t_vec3		color;
	t_vec3		ambient;
	t_vec3		emt;
	t_hit		rec;

	rt_al = single_rt()->a;
	if (depth <= 0)
		return (init_vector(0.0, 0.0, 0.0));
	if (hit_objs(objs, ray, init_interval(0.001, INFINITY), &rec))
	{
		ambient.x = rt_al->ratio * rt_al->color.x * 0.001 * rec.mat->albedo.x;
		ambient.y = rt_al->ratio * rt_al->color.y * 0.001 * rec.mat->albedo.y;
		ambient.z = rt_al->ratio * rt_al->color.z * 0.001 * rec.mat->albedo.z;
		// emt = vscale(rec.mat->emit_color, 1.0);
		// emt = vadd(emt, vscale(ray_light(&rec, objs), 1.0));
		emt = vscale(ray_light(&rec, objs), 1.0);
		if (scatter(&ray, &rec, &color))
		{
			if (rec.mat->type == 1 || rec.mat->type == 2)
			{
				// return (vadd(vmult(ray_color(ray, depth - 1, objs), color), vadd(ambient, emt)));
				return vadd(vadd(ambient, emt), ray_color(ray, depth - 1, objs));
			}
			return (vadd(ambient, emt));
		}
		else
		{
			return (single_cam()->background);
			// return (vadd(ambient, emt));
		}
	}
	// a = 0.5 * (vunit(ray.direction).y + 1.0);
	// color = vscale(init_vector(1.0, 1.0, 1.0), 1.0 - a);
	// color = vadd(color, vscale(init_vector(0.5, 0.7, 1.0), a));
	return (single_cam()->background);
}
