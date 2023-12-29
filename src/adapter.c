/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adapter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 21:47:56 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/29 20:00:41 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	append_obj(t_obj *target)
{
	int			i;
	t_resource	*rsc;

	i = 0;
	rsc = single_rsc();
	while (rsc->objs[i] != NULL)
		i++;
	rsc->objs[i] = target;
	target->id = i;
	target->nth = i;
	rsc->len_objs++;
}

void	append_mat(t_material *target, char *name)
{
	int			i;
	t_resource	*rsc;

	i = 0;
	rsc = single_rsc();
	ft_strlcpy(target->name, name, ft_strlen(name) + 1);
	while (rsc->mats[i] != NULL)
		i++;
	rsc->mats[i] = target;
	rsc->len_objs++;
}

t_material	*find_mat(char *name)
{
	int			i;
	t_resource	*rsc;

	i = 0;
	rsc = single_rsc();
	while (rsc->mats[i] != NULL)
	{
		if (ft_strncmp(name, rsc->mats[i]->name, ft_strlen(name)) == 0)
			return (rsc->mats[i]);
		i++;
	}
	return (NULL);
}

void	append_box(t_vec3 a, t_vec3 b, t_material *mat, double angle, t_vec3 offset)
{
	t_vec3	min;
	t_vec3	max;
	t_vec3	dx;
	t_vec3	dy;
	t_vec3	dz;
	t_plane	*plane;

	min = init_vector(fmin(a.x, b.x), fmin(a.y, b.y), fmin(a.z, b.z));
	max = init_vector(fmax(a.x, b.x), fmax(a.y, b.y), fmax(a.z, b.z));
	dx = init_vector(max.x - min.x, 0, 0);
	dy = init_vector(0, max.y - min.y, 0);
	dz = init_vector(0, 0, max.z - min.z);
	plane = init_plane(init_vector(min.x, min.y, max.z), dx, dy, mat);			// front
	plane->rotate_angle = angle;
	plane->translate = offset;
	append_obj(init_obj((void *)plane, PLANE, plane->mat));
	plane = init_plane(init_vector(max.x, min.y, max.z), vflip(dz), dy, mat);	// right
	plane->rotate_angle = angle;
	plane->translate = offset;
	append_obj(init_obj((void *)plane, PLANE, plane->mat));
	plane = init_plane(init_vector(max.x, min.y, min.z), vflip(dx), dy, mat);	// back
	plane->rotate_angle = angle;
	plane->translate = offset;
	append_obj(init_obj((void *)plane, PLANE, plane->mat));
	plane = init_plane(init_vector(min.x, min.y, min.z), dz, dy, mat);			// left
	plane->rotate_angle = angle;
	plane->translate = offset;
	append_obj(init_obj((void *)plane, PLANE, plane->mat));
	plane = init_plane(init_vector(min.x, max.y, max.z), dx, vflip(dz), mat);	// top
	plane->rotate_angle = angle;
	plane->translate = offset;
	append_obj(init_obj((void *)plane, PLANE, plane->mat));
	plane = init_plane(init_vector(min.x, min.y, min.z), dx, dz, mat);			// bottom
	plane->rotate_angle = angle;
	plane->translate = offset;
	append_obj(init_obj((void *)plane, PLANE, plane->mat));
}

void	apply_dotrt(t_dotrt *rt)
{
	int			i;
	t_material	*mat_default;
	t_material	*mat_light;
	t_subrt		*subrt;
	t_sphere	*sp;
	t_plane		*pl;
	t_rectangle	*re;
	t_cylinder	*cy;
	t_obj		*obj;

	// mat_light = init_material(0, rt->l->color, 0, 0);
	// mat_light->emit_color = vscale((t_vec3){1, 1, 1}, rt->l->ratio);
	// mat_light->emit_color = vscale(rt->l->color, 5);
	// append_mat(mat_light, "light");

	// sp = init_sphere(init_vector(0, 0, 0), 10, mat_light);
	// sp->translate = rt->l->point;
	// obj = init_obj((void *)sp, SPHERE, sp->mat);
	
	// pl = init_plane(init_vector(0, 0, 0), (t_vec3){1, 0, 0}, (t_vec3){0, 0, 1}, mat_light);
	// pl->translate = rt->l->point;
	// obj = init_obj((void *)pl, PLANE, pl->mat);

	// re = init_rectangle(init_vector(0, 0, 0), (t_vec3){1, 0, 0}, (t_vec3){0, 0, 1}, mat_light);
	// re->translate = rt->l->point;
	// re->normal = (t_vec3){-(re->translate.y), re->translate.x, 0};
	// obj = init_obj((void *)re, RECTANGLE, re->mat);
	
	// append_obj(obj);
	
	i = -1;
	while (rt->sp[++i])
	{
		subrt = rt->sp[i];
		mat_default = init_material(2, subrt->color, 0, 0);
		append_mat(mat_default, "");
		ft_strlcat(mat_default->name, "sp", 3);
		sp = init_sphere(subrt->point, subrt->value1, mat_default);
		obj = init_obj((void *)sp, SPHERE, sp->mat);
		append_obj(obj);
	}
	re = init_rectangle(init_vector(0, -10, 10), (t_vec3){0, 10, 0}, (t_vec3){10, 0, 0}, mat_default);
	// re->translate = (t_vec3){0, -10, 10};
	// re->normal = (t_vec3){-(re->translate.y), re->translate.x, 0};
	obj = init_obj((void *)re, RECTANGLE, re->mat);
	append_obj(obj);
	i = -1;
	while (rt->pl[++i])
	{
		subrt = rt->pl[i];
		mat_default = init_material(0, subrt->color, 0, 0);
		append_mat(mat_default, "");
		ft_strlcat(mat_default->name, "pl", 3);
		pl = init_plane(subrt->point, init_vector(0, 0, 0), init_vector(0, 0, 0), mat_default);
		pl->normal = subrt->vector;
		obj = init_obj((void *)pl, PLANE, pl->mat);
		append_obj(obj);
	}
	i = -1;
	while (rt->cy[++i])
	{
		subrt = rt->cy[i];
		mat_default = init_material(2, subrt->color, 0, 1.5);
		append_mat(mat_default, "");
		ft_strlcat(mat_default->name, "cy", 3);
		cy = init_cylinder(subrt->point, subrt->value1, subrt->value2, mat_default);
		cy->normal = subrt->vector;
		obj = init_obj((void *)cy, CYLINDER, cy->mat);
		append_obj(obj);
	}
	
}
