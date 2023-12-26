/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 13:36:00 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/24 18:05:42 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"
#include "vector.h"

t_material	*init_material(int type, t_vec3 color, double fuzz, double ir)
{
	t_material	*this;

	this = malloc(sizeof(t_material) * 1);
	this->type = type;
	this->albedo = color;
	this->fuzz = 1;
	if (fuzz < 1)
		this->fuzz = fuzz;
	this->index_of_refraction = ir;
	this->emit_color = init_vector(0, 0, 0);
	ft_bzero(this->name, 64);
	return (this);
}

static double	reflectance(double cosine, double ref_idx)
{
	double	r0;

	r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return (r0 + (1 - r0) *pow((1 - cosine), 5));
}

t_bool	scatter(t_ray *r, t_hit *rec, t_vec3 *color)
{
	if (rec->mat->type == 0)	// lambertian
	{
		t_vec3	scatter_direction;

		scatter_direction = vadd(rec->normal, vrandom_unit_vector());
		if (vnear_zero(scatter_direction))
			scatter_direction = rec->normal;
		*r = init_ray(rec->point, scatter_direction);
		*color = rec->mat->albedo;
		return (1);
	}
	else if (rec->mat->type == 1)	// metal
	{
		t_vec3	reflected;

		reflected = vreflect(vunit(r->direction), rec->normal);
		reflected = vadd(reflected, \
				vscale(vrandom_unit_vector(), rec->mat->fuzz));
		*r = init_ray(rec->point, reflected);
		*color = rec->mat->albedo;
		return (vdot(r->direction, rec->normal) > 0);
	}
	else if (rec->mat->type == 2)	// dielectric
	{
		double	refraction_ratio;
		t_vec3	unit_direction;
		double	cos_theta;
		double	sin_theta;
		t_bool	cannot_refract;
		t_vec3	direction;

		*color = init_vector(1.0, 1.0, 1.0);
		if (rec->front_face)
			refraction_ratio = (1.0 / rec->mat->index_of_refraction);
		else
			refraction_ratio = rec->mat->index_of_refraction;
		unit_direction = vunit(r->direction);
		cos_theta = fmin(vdot(vflip(unit_direction), rec->normal), 1.0);
		sin_theta = sqrt(1.0 - cos_theta * cos_theta);
		cannot_refract = refraction_ratio * sin_theta > 1.0;
		if (cannot_refract || reflectance(cos_theta, refraction_ratio) > ft_randdouble())
			direction = vreflect(unit_direction, rec->normal);
		else
			direction = vrefract(unit_direction, rec->normal, refraction_ratio);
		*r = init_ray(rec->point, direction);
		return (1);
	}
	return (0);
}
