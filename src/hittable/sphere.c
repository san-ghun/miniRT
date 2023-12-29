/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 01:00:50 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/28 20:53:31 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"

t_sphere	*init_sphere(t_vec3 center, double radius, t_material *material)
{
	t_sphere	*this;

	this = malloc(sizeof(t_sphere) * 1);
	this->center = center;
	this->radius = radius;
	this->mat = material;
	this->tex = NULL;
	this->translate = init_vector(0, 0, 0);
	this->rotate_angle = 0;
	return (this);
}

static t_bool	check_root(t_sphere *sp, t_ray ray, double *t, double lim)
{
	t_vec3	oc = vsubtract(ray.origin, sp->center);

	double 	a = vlen_pow(ray.direction);
	double	half_b = vdot(oc, ray.direction);
	double	c = vlen_pow(oc) - (sp->radius * sp->radius);
	double	discriminant = half_b * half_b - a * c;

	if (discriminant < 0)
		return (0);
	double	sqrtd = sqrt(discriminant);

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

	sp = (t_sphere *)data;

	t_bool	is_rotate;
	is_rotate = sp->rotate_angle != 0;
	t_bool	is_translate;
	is_translate = (sp->translate.x != 0 || sp->translate.y != 0 || sp->translate.z != 0);

	if (is_translate)
		ray.origin = vsubtract(ray.origin, sp->translate);
	double	radians = sp->rotate_angle * M_PI / 180.0;
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

	if (check_root(sp, ray, &root, interval.max) != 1)
		return (0);

	rec->t = root;
	rec->point = ray_at(ray, root);
	t_vec3	outward_normal = vscale(vsubtract(rec->point, sp->center), 1.0 / sp->radius);
	set_face_normal(rec, ray, outward_normal);
	rec->mat = sp->mat;

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
		rec->point = vadd(rec->point, sp->translate);

	return (1);
}

t_bool	interfere_sp(void *data, t_ray r, double lim)
{
	double 		t;
	t_sphere	*sp;

	sp = (t_sphere *)data;
	if (check_root(sp, r, &t, lim) != 1)
		return (0);
	return (1);
}
