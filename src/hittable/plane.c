/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 00:15:27 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/30 00:38:23 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"
#include <math.h>

static t_bool	check_root(t_plane *pl, t_ray ray, double *t, double lim)
{
	double	denom;

	denom = vdot(pl->normal, ray.direction);
	if (!denom)
		return (0);
	*t = vdot(vsubtract(pl->point, ray.origin), pl->normal) / denom;
	if (*t < 0.001 || *t > lim)
		return (0);
	return (1);
}

t_bool	hit_plane(void *data, t_ray ray, t_interval interval, t_hit *rec)
{
	t_plane	*pl;
	double	t;
	t_bool	is_translate;
	t_vec3	intersection;

	pl = (t_plane *)data;
	is_translate = (pl->translate.x != 0 || pl->translate.y != 0 \
					|| pl->translate.z != 0);
	if (is_translate)
		ray.origin = vsubtract(ray.origin, pl->translate);
	if (pl->rotate_angle != 0)
		pre_rotate(&ray, pl->rotate_angle * M_PI / 180.0);
	if (check_root(pl, ray, &t, interval.max) != 1)
		return (0);
	intersection = ray_at(ray, t);
	rec->t = t;
	rec->point = intersection;
	set_face_normal(rec, ray, pl->normal);
	rec->mat = pl->mat;
	if (pl->rotate_angle != 0)
		post_rotate(rec, pl->rotate_angle * M_PI / 180.0);
	if (is_translate)
		rec->point = vadd(rec->point, pl->translate);
	return (1);
}

t_bool	interfere_pl(void *data, t_ray r, double lim)
{
	double		t;
	t_plane		*pl;

	pl = (t_plane *)data;
	if (check_root(pl, r, &t, lim) != 1)
		return (0);
	return (1);
}
