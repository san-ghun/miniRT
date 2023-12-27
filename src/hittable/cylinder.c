/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 23:07:52 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/27 18:12:26 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"
#include <math.h>

t_cylinder	*init_cylinder(t_vec3 center, double radius, double height, t_material *material)
{
	t_cylinder	*this;

	this = malloc(sizeof(t_cylinder) * 1);
	this->center = center;
	this->normal = init_vector(0, 1, 0);
	this->radius = radius;
	this->height = height;
	this->tc = vadd(this->center, vscale(this->normal, this->height / 2));
	this->bc = vsubtract(this->center, vscale(this->normal, this->height / 2));
	this->mat = material;
	this->tex = NULL;
	this->translate = init_vector(0, 0, 0);
	this->rotate_angle = 0;
	return (this);
}

double	root_rectangle(t_cylinder *cy, t_ray ray, t_interval interval)
{
	double	root;
	
	t_vec3	v = vsubtract(ray.origin, cy->center);
	double 	a = vlen_pow(vcross(ray.direction, cy->normal));
	double	half_b = vdot(vcross(ray.direction, cy->normal), vcross(v, cy->normal));
	double	c = vlen_pow(vcross(v, cy->normal)) - (cy->radius * cy->radius);
	double	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (INFINITY);
	double	sqrtd = sqrt(discriminant);
	root = (-half_b - sqrtd) / a;
	if (!surrounds(interval, root))
	{
		root = (-half_b + sqrtd) / a;
		if (!surrounds(interval, root))
			return (INFINITY);
	}
	if (vdot(cy->normal, vsubtract(vadd(ray.origin, vscale(ray.direction, root)), cy->tc)) > 0)
		return (INFINITY);
	if (vdot(cy->normal, vsubtract(vadd(ray.origin, vscale(ray.direction, root)), cy->bc)) < 0)
		return (INFINITY);
	return (root);
}

double	root_circle(t_cylinder *cy, t_ray ray, t_interval interval)
{
	double	root_circ;

	double	denom = vdot(ray.direction, cy->normal);
	if (fabs(denom) < 1e-8)
		return (INFINITY);
	t_vec3	tv = vsubtract(cy->tc, ray.origin);
	double	tt = vdot(tv, cy->normal) / denom;
	if (vlen_pow(vsubtract(vadd(ray.origin, vscale(ray.direction, tt)), cy->tc)) > cy->radius * cy->radius)
		tt = INFINITY;
	t_vec3	bv = vsubtract(cy->bc, ray.origin);
	double	bt = vdot(bv, cy->normal) / denom;
	if (vlen_pow(vsubtract(vadd(ray.origin, vscale(ray.direction, bt)), cy->bc)) > cy->radius * cy->radius)
		bt = INFINITY;
	if (!surrounds(interval, tt))
		tt = INFINITY;
	if (!surrounds(interval, bt))
		bt = INFINITY;
	if (tt < bt)
		root_circ = tt;
	else
		root_circ = bt;
	return (root_circ);
}

t_bool	hit_cylinder(void *data, t_ray ray, t_interval interval, t_hit *rec)
{
	t_cylinder	*cy;

	cy = (t_cylinder *)data;

	t_bool	is_rotate;
	is_rotate = cy->rotate_angle != 0;
	t_bool	is_translate;
	is_translate = (cy->translate.x != 0 || cy->translate.y != 0 || cy->translate.z != 0);

	if (is_translate)
	{
		ray.origin = vsubtract(ray.origin, cy->translate);
	}
	double	radians = cy->rotate_angle * M_PI / 180.0;
	double	sin_theta = sin(radians);
	double	cos_theta = cos(radians);
	t_vec3	origin = ray.origin;
	t_vec3	direction = ray.direction;
	if (is_rotate)
	{
		origin.x = cos_theta * ray.origin.x - sin_theta * ray.origin.z;
		origin.z = sin_theta * ray.origin.x + cos_theta * ray.origin.z;
		direction.x = cos_theta * ray.direction.x - sin_theta * ray.direction.z;
		direction.z = sin_theta * ray.direction.x + cos_theta * ray.direction.z;
		ray.origin = origin;
		ray.direction = direction;
	}

	cy->tc = vadd(cy->center, vscale(cy->normal, cy->height / 2));
	cy->bc = vsubtract(cy->center, vscale(cy->normal, cy->height / 2));
	// get root for rectangle
	double	root_rect;
	root_rect = root_rectangle(cy, ray, interval);

	// get root for circle
	double	root_circ;
	root_circ = root_circle(cy, ray, interval);

	if (root_rect == INFINITY && root_circ == INFINITY)
		return (0);
	if (root_rect < root_circ)
	{
		rec->t = root_rect;
		rec->point = ray_at(ray, root_rect);
		t_vec3	outward_normal = vunit(vsubtract(rec->point, vadd(vscale(cy->normal, vdot(cy->normal, vsubtract(rec->point, cy->center))), cy->center)));
		set_face_normal(rec, ray, outward_normal);
	}
	else
	{
		rec->t = root_circ;
		rec->point = ray_at(ray, root_circ);
		t_vec3	outward_normal = cy->normal;
		set_face_normal(rec, ray, outward_normal);
	}
	rec->mat = cy->mat;

	t_vec3	point = rec->point;
	t_vec3	normal = rec->normal;
	if (is_rotate)
	{
		point.x = cos_theta * rec->point.x + sin_theta * rec->point.z;
		point.z = -sin_theta * rec->point.x + cos_theta * rec->point.z;
		normal.x = cos_theta * rec->normal.x + sin_theta * rec->normal.z;
		normal.z = -sin_theta * rec->normal.x + cos_theta * rec->normal.z;
		rec->point = point;
		rec->normal = normal;
	}
	if (is_translate)
	{
		rec->point = vadd(rec->point, cy->translate);
	}

	return (1);
}
