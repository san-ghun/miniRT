/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 01:00:50 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/30 00:15:17 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"

static t_bool	check_root(t_sphere *sp, t_ray ray, double *t, double lim)
{
	t_vec3	oc;
	double	a;
	double	half_b;
	double	c;
	double	sqrtd;

	oc = vsubtract(ray.origin, sp->center);
	a = vlen_pow(ray.direction);
	half_b = vdot(oc, ray.direction);
	c = vlen_pow(oc) - (sp->radius * sp->radius);
	if (half_b * half_b - a * c < 0)
		return (0);
	sqrtd = sqrt(half_b * half_b - a * c);
	*t = (-half_b - sqrtd) / a;
	if (*t < 0.001 || *t > lim)
	{
		*t = (-half_b + sqrtd) / a;
		if (*t < 0.001 || *t > lim)
			return (0);
	}
	return (1);
}

t_bool	hit_sphere(void *data, t_ray ray, t_interval interval, t_hit *rec)
{
	t_sphere	*sp;
	double		root;
	t_bool		is_translate;
	t_vec3		outward_normal;

	sp = (t_sphere *)data;
	is_translate = (sp->translate.x != 0 || sp->translate.y != 0 \
					|| sp->translate.z != 0);
	if (is_translate)
		ray.origin = vsubtract(ray.origin, sp->translate);
	if (sp->rotate_angle != 0)
		pre_rotate(&ray, sp->rotate_angle * M_PI / 180.0);
	if (check_root(sp, ray, &root, interval.max) != 1)
		return (0);
	rec->t = root;
	rec->point = ray_at(ray, root);
	outward_normal = vscale(vsubtract(rec->point, sp->center), \
							1.0 / sp->radius);
	set_face_normal(rec, ray, outward_normal);
	rec->mat = sp->mat;
	if (sp->rotate_angle != 0)
		post_rotate(rec, sp->rotate_angle * M_PI / 180.0);
	if (is_translate)
		rec->point = vadd(rec->point, sp->translate);
	return (1);
}

t_bool	interfere_sp(void *data, t_ray r, double lim)
{
	double		t;
	t_sphere	*sp;

	sp = (t_sphere *)data;
	if (check_root(sp, r, &t, lim) != 1)
		return (0);
	return (1);
}
