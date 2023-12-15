/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 01:00:50 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/15 20:06:26 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"

t_sphere	*init_sphere(t_vec3 center, double radius)
{
	t_sphere	*this;

	this = malloc(sizeof(t_sphere) * 1);
	this->center = center;
	this->radius = radius;
	return (this);
}

t_bool	hit_sphere(void *data, t_ray ray, t_interval interval, t_hit *rec)
{
	t_sphere	*sp;

	sp = (t_sphere *)data;
	t_vec3	oc = subtract(ray.origin, sp->center);

	double 	a = len_pow(ray.direction);
	double	half_b = dot(oc, ray.direction);
	double	c = len_pow(oc) - (sp->radius * sp->radius);
	double	discriminant = half_b * half_b - a * c;

	if (discriminant < 0)
		return (0);
	double	sqrtd = sqrt(discriminant);

	double	root = (-half_b - sqrtd) / a;
	if (!surrounds(interval, root))
	{
		root = (-half_b + sqrtd) / a;
		if (!surrounds(interval, root))
			return (0);
	}

	rec->t = root;
	rec->point = ray_at(ray, root);
	t_vec3	outward_normal = scale(subtract(rec->point, sp->center), 1.0 / sp->radius);
	set_face_normal(rec, ray, outward_normal);

	return (1);
}
