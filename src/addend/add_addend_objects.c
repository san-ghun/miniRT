/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:20:11 by minakim           #+#    #+#             */
/*   Updated: 2024/02/09 19:39:33 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "addend.h"

t_plane	*pl_add_position(t_plane *pl, t_aes addend)
{
	t_vec3	n;
	t_vec3	nomal;

	if (!vecequ(addend.position, non_set()))
	{
		nomal = pl->normal;
		pl->point = vadd(pl->point, addend.position);
		pl->box = aabb_pad(init_aabb_vec(pl->point, \
			vadd(pl->point, vadd(pl->u, pl->v))));
		n = vcross(pl->u, pl->v);
		pl->normal = vunit(n);
		pl->d = vdot(pl->normal, pl->point);
		pl->w = vscale(n, 1 / vdot(n, n));
		pl->normal = nomal;
		pl->d = vdot(pl->normal, pl->point);
	}
	return (pl);
}

t_sphere	*sp_add_position(t_sphere *sp, t_aes addend)
{
	if (!vecequ(addend.position, non_set()))
	{
		sp->center = vadd(sp->center, addend.position);
	}
	return (sp);
}

t_cylinder	*cy_add_position(t_cylinder *cy, t_aes addend)
{
	t_vec3	nomal;

	if (!vecequ(addend.position, non_set()))
	{
		nomal = cy->normal;
		cy->center = vadd(cy->center, addend.position);
		cy->tc = vadd(cy->center, vscale(cy->normal, cy->height / 2));
		cy->bc = vsubtract(cy->center, vscale(cy->normal, cy->height / 2));
		cy->normal = nomal;
		cy->tc = vadd(cy->center, vscale(cy->normal, cy->height / 2));
		cy->bc = vsubtract(cy->center, vscale(cy->normal, cy->height / 2));
	}
	return (cy);
}

void	set_point_with_addend(t_obj *obj, t_aes addend)
{
	if (addend.type == PLANE)
		obj->data = (void *)pl_add_position((t_plane *)obj->data, addend);
	else if (addend.type == SPHERE)
		obj->data = (void *)sp_add_position((t_sphere *)obj->data, addend);
	else if (addend.type == CYLINDER)
		obj->data = (void *)cy_add_position((t_cylinder *)obj->data, addend);
	return ;
}
