/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_record.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 01:25:50 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/30 01:08:16 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"

t_hit	init_rec(void)
{
	t_hit	this;

	this.front_face = 0;
	this.normal = init_vector(0, 0, 0);
	this.point = init_vector(0, 0, 0);
	this.mat = NULL;
	this.tex = NULL;
	this.t = 0;
	this.u = 0;
	this.v = 0;
	return (this);
}

void	set_hit_point(t_hit *rec, t_ray ray, double root)
{
	rec->t = root;
	rec->point = ray_at(ray, root);
}

void	set_face_normal(t_hit *rec, t_ray ray, t_vec3 outward_normal)
{
	rec->front_face = vdot(ray.direction, outward_normal) < 0;
	if (rec->front_face)
		rec->normal = outward_normal;
	else
		rec->normal = vflip(outward_normal);
}

t_bool	hit_objs(t_obj *objs[], t_ray ray, t_interval interval, t_hit *rec)
{
	t_bool		hit_anything;
	double		closest_so_far;
	t_interval	ray_t;
	int			i;

	hit_anything = 0;
	closest_so_far = interval.max;
	i = -1;
	while (objs[++i] != NULL)
	{
		ray_t = init_interval(interval.min, closest_so_far);
		if ((objs[i]->type == SPHERE && \
			hit_sphere((void *)(objs[i]->data), ray, ray_t, rec))
		|| (objs[i]->type == PLANE && \
			hit_plane((void *)(objs[i]->data), ray, ray_t, rec))
		|| (objs[i]->type == CYLINDER && \
			hit_cylinder((void *)(objs[i]->data), ray, ray_t, rec)))
		{
			hit_anything = 1;
			closest_so_far = rec->t;
			rec->mat = objs[i]->material;
		}
	}
	return (hit_anything);
}
