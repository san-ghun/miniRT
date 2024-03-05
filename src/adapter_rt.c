/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adapter_rt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 21:53:32 by sanghupa          #+#    #+#             */
/*   Updated: 2024/01/27 19:01:27 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	apply_sp(t_dotrt *rt)
{
	int			i;
	t_subrt		*subrt;
	t_material	*mat_default;
	t_sphere	*sp;
	t_obj		*obj;

	i = -1;
	while (rt->sp[++i])
	{
		subrt = rt->sp[i];
		mat_default = init_material(0, subrt->color, 0, 0);
		if (subrt->mat_type == 1)
			mat_default->fuzz = subrt->mat_value;
		if (subrt->mat_type == 2)
			mat_default->index_of_refraction = subrt->mat_value;
		append_mat(mat_default, "");
		ft_strlcat(mat_default->name, "sp", 3);
		sp = init_sphere(subrt->point, subrt->value1, mat_default);
		obj = init_obj((void *)sp, SPHERE, sp->mat);
		append_obj(obj);
	}
}

static void	apply_pl(t_dotrt *rt)
{
	int			i;
	t_subrt		*subrt;
	t_material	*mat_default;
	t_plane		*pl;
	t_obj		*obj;

	i = -1;
	while (rt->pl[++i])
	{
		subrt = rt->pl[i];
		mat_default = init_material(subrt->mat_type, subrt->color, 0, 0);
		if (subrt->mat_type == 1)
			mat_default->fuzz = subrt->mat_value;
		if (subrt->mat_type == 2)
			mat_default->index_of_refraction = subrt->mat_value;
		append_mat(mat_default, "");
		ft_strlcat(mat_default->name, "pl", 3);
		pl = init_plane(subrt->point, \
				init_vector(0, 0, 0), init_vector(0, 0, 0), mat_default);
		pl->normal = subrt->vector;
		pl->d = vdot(pl->normal, pl->point);
		obj = init_obj((void *)pl, PLANE, pl->mat);
		append_obj(obj);
	}
}

static void	apply_cy(t_dotrt *rt)
{
	int			i;
	t_subrt		*subrt;
	t_material	*mat_default;
	t_cylinder	*cy;
	t_obj		*obj;

	i = -1;
	while (rt->cy[++i])
	{
		subrt = rt->cy[i];
		mat_default = init_material(subrt->mat_type, subrt->color, 0, 0);
		if (subrt->mat_type == 1)
			mat_default->fuzz = subrt->mat_value;
		if (subrt->mat_type == 2)
			mat_default->index_of_refraction = subrt->mat_value;
		append_mat(mat_default, "");
		ft_strlcat(mat_default->name, "cy", 3);
		cy = init_cylinder(subrt->point, \
				subrt->value1, subrt->value2, mat_default);
		cy->normal = subrt->vector;
		cy->tc = vadd(cy->center, vscale(cy->normal, cy->height / 2));
		cy->bc = vsubtract(cy->center, vscale(cy->normal, cy->height / 2));
		obj = init_obj((void *)cy, CYLINDER, cy->mat);
		append_obj(obj);
	}
}

void	apply_dotrt(t_dotrt *rt)
{
	apply_sp(rt);
	apply_pl(rt);
	apply_cy(rt);
}
