/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 18:34:37 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/31 01:58:34 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include <math.h>
#include <stdio.h>

static t_bool	in_shadow(t_ray ray, double lim, t_obj *objs[])
{
	int	i;

	i = -1;
	while (objs[++i] != NULL)
	{
		if (objs[i]->type == SPHERE && \
			interfere_sp((void *)objs[i]->data, ray, lim))
			return (1);
		else if (objs[i]->type == PLANE && \
				interfere_pl((void *)objs[i]->data, ray, lim))
			return (1);
		else if (objs[i]->type == CYLINDER && \
				interfere_cy((void *)objs[i]->data, ray, lim))
			return (1);
	}
	return (0);
}

// static t_vec3	modify_light_color()
// {}

static t_vec3	point_light_get(t_hit *rec, t_subrt *rt_l, t_obj *objs[])
{
	t_vec3	diffuse;
	t_vec3	light_dir;
	double	light_len;
	t_ray	light_ray;

	light_dir = vsubtract(rt_l->point, rec->point);
	light_len = vlen_sqrt(light_dir);
	light_dir = vunit(light_dir);
	light_ray = init_ray(vadd(rec->point, vscale(rec->normal, 1e-4)), \
							light_dir);
	if (in_shadow(light_ray, light_len, objs) || (rt_l->ratio == 0.0))
		return ((t_vec3){0.0, 0.0, 0.0});
	rt_l->vector2 = vscale((t_vec3){1.0, 1.0, 1.0}, rt_l->ratio);
	diffuse = vscale(rt_l->vector2, fmax(0.0, vdot(rec->normal, light_dir)));
	diffuse = vscale(vmult(diffuse, rec->mat->albedo), 30.0);
	diffuse.x = diffuse.x / (rt_l->vector2.x + \
				rt_l->vector2.x * 0.1 * light_len + \
				rt_l->vector2.x * 0.02 * light_len * light_len);
	diffuse.y = diffuse.y / (rt_l->vector2.y + \
				rt_l->vector2.y * 0.1 * light_len + \
				rt_l->vector2.y * 0.01 * light_len * light_len);
	diffuse.z = diffuse.z / (rt_l->vector2.z + \
				rt_l->vector2.z * 0.1 * light_len + \
				rt_l->vector2.z * 0.01 * light_len * light_len);
	return (vscale(diffuse, rt_l->ratio));
}

static t_vec3	phong_lighting(t_hit *rec, t_obj *objs[])
{
	t_subrt	*rt_al;
	t_subrt	*rt_l;
	t_vec3	ambient;
	t_vec3	light_color;

	rt_al = single_rt()->a;
	rt_l = single_rt()->l;
	ambient = vscale(rt_al->color, rt_al->ratio);
	ambient = vmult(ambient, rec->mat->albedo);
	ambient = vscale(ambient, 0.001);
	light_color = (t_vec3){0.0, 0.0, 0.0};
	light_color = vadd(light_color, point_light_get(rec, rt_l, objs));
	light_color = vadd(light_color, ambient);
	return (light_color);
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
		emt = phong_lighting(&rec, objs);
		if (scatter(&ray, &rec, &color))
		{
			if (rec.mat->type == 1 || rec.mat->type == 2)
				return (vadd(vmult(ray_color(ray, depth - 1, objs), \
						color), emt));
			return (emt);
		}
		return (single_cam()->background);
	}
	return (single_cam()->background);
}
