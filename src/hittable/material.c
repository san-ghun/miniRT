/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 13:36:00 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/18 11:59:25 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"
#include "vector.h"

t_material	init_material(int type, t_vec3 color, double fuzz, double ir)
{
	t_material	this;

	this.type = type;
	this.albedo = color;
	this.fuzz = 1;
	if (fuzz < 1)
		this.fuzz = fuzz;
	this.index_of_refraction = ir;
	return (this);
}

t_bool	scatter(t_ray *r, t_hit *rec, t_vec3 *color)
{
	t_vec3	scatter_direction;
	t_vec3	reflected;
	t_vec3	refracted;
	double	refraction_ratio;
	t_vec3	attenuation;

	if (rec->mat->type == 0)	// lambertian
	{
		scatter_direction = vadd(rec->normal, vrandom_unit_vector());
		if (vnear_zero(scatter_direction))
			scatter_direction = rec->normal;
		*r = init_ray(rec->point, scatter_direction);
		*color = rec->mat->albedo;
		return (1);
	}
	if (rec->mat->type == 1)	// metal
	{
		reflected = vreflect(vunit(r->direction), rec->normal);
		reflected = vadd(reflected, \
				vscale(vrandom_unit_vector(), rec->mat->fuzz));
		*r = init_ray(rec->point, reflected);
		*color = rec->mat->albedo;
		return (vdot(r->direction, rec->normal) > 0);
	}
	if (rec->mat->type == 2)	// dielectric
	{
		if (rec->front_face)
			refraction_ratio = (1.0 / rec->mat->index_of_refraction);
		else
			refraction_ratio = rec->mat->index_of_refraction;
		refracted = vrefract(vunit(r->direction), rec->normal, refraction_ratio);
		*r = init_ray(rec->point, refracted);
		*color = init_vector(1.0, 1.0, 1.0);
		return (1);
	}
	return (0);
}
