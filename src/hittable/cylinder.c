/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 23:07:52 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/30 01:08:18 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"
#include <math.h>

static double	root_rectangle(t_cylinder *cy, \
								t_vec3 r_o, t_vec3 r_d, double lim)
{
	double	root;
	t_vec3	v;
	double	a;
	double	half_b;
	double	c;

	v = vsubtract(r_o, cy->center);
	a = vlen_pow(vcross(r_d, cy->normal));
	half_b = vdot(vcross(r_d, cy->normal), vcross(v, cy->normal));
	c = vlen_pow(vcross(v, cy->normal)) - (cy->radius * cy->radius);
	if (half_b * half_b - a * c < 0)
		return (INFINITY);
	root = (-half_b - sqrt(half_b * half_b - a * c)) / a;
	if (root < 0.001 || root > lim)
	{
		root = (-half_b + sqrt(half_b * half_b - a * c)) / a;
		if (root < 0.001 || sqrt(half_b * half_b - a * c) > lim)
			return (INFINITY);
	}
	if (vdot(cy->normal, vsubtract(vadd(r_o, vscale(r_d, root)), cy->tc)) > 0)
		return (INFINITY);
	if (vdot(cy->normal, vsubtract(vadd(r_o, vscale(r_d, root)), cy->bc)) < 0)
		return (INFINITY);
	return (root);
}

static double	root_circle(t_cylinder *cy, t_vec3 r_o, t_vec3 r_d, double lim)
{
	double	denom;
	double	tt;
	double	bt;

	denom = vdot(r_d, cy->normal);
	if (fabs(denom) < 1e-8)
		return (INFINITY);
	tt = vdot(vsubtract(cy->tc, r_o), cy->normal) / denom;
	if (vlen_pow(vsubtract(vadd(r_o, vscale(r_d, tt)), cy->tc)) > \
			cy->radius * cy->radius)
		tt = INFINITY;
	bt = vdot(vsubtract(cy->bc, r_o), cy->normal) / denom;
	if (vlen_pow(vsubtract(vadd(r_o, vscale(r_d, bt)), cy->bc)) > \
			cy->radius * cy->radius)
		bt = INFINITY;
	if (tt < 0.001 || tt > lim)
		tt = INFINITY;
	if (bt < 0.001 || bt > lim)
		bt = INFINITY;
	if (tt < bt)
		return (tt);
	return (bt);
}

t_bool	hit_cylinder(void *data, t_ray ray, t_interval interval, t_hit *rec)
{
	t_cylinder	*cy;
	double		root_rect;
	double		root_circ;

	cy = (t_cylinder *)data;
	ray.origin = vsubtract(ray.origin, cy->translate);
	if (cy->rotate_angle != 0)
		pre_rotate(&ray, cy->rotate_angle * M_PI / 180.0);
	root_rect = root_rectangle(cy, ray.origin, ray.direction, interval.max);
	root_circ = root_circle(cy, ray.origin, ray.direction, interval.max);
	if (root_rect == INFINITY && root_circ == INFINITY)
		return (0);
	set_hit_point(rec, ray, root_circ);
	set_face_normal(rec, ray, cy->normal);
	if (root_rect < root_circ)
	{
		set_hit_point(rec, ray, root_rect);
		set_face_normal(rec, ray, vunit(vsubtract(rec->point, \
			vadd(vscale(cy->normal, vdot(cy->normal, \
				vsubtract(rec->point, cy->center))), cy->center))));
	}
	if (cy->rotate_angle != 0)
		post_rotate(rec, cy->rotate_angle * M_PI / 180.0);
	rec->point = vadd(rec->point, cy->translate);
	return (1);
}

t_bool	interfere_cy(void *data, t_ray r, double lim)
{
	double		root_r;
	double		root_c;
	t_cylinder	*cy;

	cy = (t_cylinder *)data;
	root_r = root_rectangle(cy, r.origin, r.direction, lim);
	root_c = root_circle(cy, r.origin, r.direction, lim);
	if (root_r == INFINITY && root_c == INFINITY)
		return (0);
	return (1);
}
