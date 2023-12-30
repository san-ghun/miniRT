/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 00:14:50 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/30 00:15:43 by sanghupa         ###   ########.fr       */
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

t_cylinder	*init_cylinder(t_vec3 center, double radius, \
							double height, t_material *material)
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
