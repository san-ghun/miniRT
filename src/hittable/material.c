/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 13:36:00 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/16 16:55:16 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"
#include "vector.h"

t_material	init_material(int type, t_vec3 color)
{
	t_material	this;

	this.type = type;
	this.albedo = color;
	return (this);
}

t_bool	scatter(t_ray *r, t_hit *rec)
{
	t_vec3	scatter_direction;

	if (rec->mat->type == 0)	// lambertian
	{
		scatter_direction = vadd(rec->normal, vrandom_unit_vector());
		if (vnear_zero(scatter_direction))
			scatter_direction = rec->normal;
		*r = init_ray(rec->point, scatter_direction);
		return (1);
	}
	if (rec->mat->type == 1)	// metal
	{
		scatter_direction = vreflect(vunit(r->direction), rec->normal);
		*r = init_ray(rec->point, scatter_direction);
		return (1);
	}
	return (0);
}
