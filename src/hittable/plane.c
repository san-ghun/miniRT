/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 00:15:27 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/26 16:11:48 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"
#include <math.h>

t_plane	*init_plane(t_vec3 point, t_vec3 u, t_vec3 v, t_material *material)
{
	t_plane	*this;
	t_vec3	n;

	this = malloc(sizeof(t_plane) * 1);
	this->point = point;
	this->u = u;
	this->v = v;
	this->box = aabb_pad(init_aabb_vec(point, vadd(point, vadd(u, v))));
	n = vcross(u, v);
	this->normal = vunit(n);
	this->d = vdot(this->normal, point);
	this->w = vscale(n, 1 / vdot(n, n));
	this->mat = material;
	this->tex = NULL;
	this->translate = init_vector(0, 0, 0);
	this->rotate_angle = 0;
	return (this);
}

static t_bool	is_interior(double a, double b, t_hit *rec)
{
	if ((a < 0) || (1 < a) || (b < 0) || (1 < b))
		return (0);
	rec->u = a;
	rec->v = b;
	return (1);
}

t_bool	hit_plane(void *data, t_ray ray, t_interval interval, t_hit *rec)
{
	t_plane	*pl;

	pl = (t_plane *)data;

	t_bool	is_rotate;
	is_rotate = pl->rotate_angle != 0;
	t_bool	is_translate;
	is_translate = (pl->translate.x != 0 || pl->translate.y != 0 || pl->translate.z != 0);

	if (is_translate)
	{
		ray.origin = vsubtract(ray.origin, pl->translate);
	}
	double	radians = pl->rotate_angle * M_PI / 180.0;
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

	double	denom = vdot(pl->normal, ray.direction);

	// No hit if the ray is parallel to the plane.
	if (fabs(denom) < 1e-8)
		return (0);

	// Return false if the hit point parameter t is outside the ray interval.
	double	t = (pl->d - vdot(pl->normal, ray.origin)) / denom;
	if (!contains(interval, t))
		return (0);

	// Determine the hit point lies within the planar shape using its plane coordinates.
	t_vec3	intersection = ray_at(ray, t);
	t_vec3	planar_hitpt_vector = vsubtract(intersection, pl->point);
	double	alpha = vdot(pl->w, vcross(planar_hitpt_vector, pl->v));
	double	beta = vdot(pl->w, vcross(pl->u, planar_hitpt_vector));

	if (!is_interior(alpha, beta, rec))
		return (0);

	rec->t = t;
	rec->point = intersection;
	set_face_normal(rec, ray, pl->normal);
	rec->mat = pl->mat;

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
		rec->point = vadd(rec->point, pl->translate);
	}

	return (1);
}
