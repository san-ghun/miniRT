/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adapter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 21:47:56 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/24 18:50:53 by sanghupa         ###   ########.fr       */
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

void	append_box(t_vec3 a, t_vec3 b, t_material *mat)
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
	append_obj(init_obj((void *)plane, PLANE, plane->mat));
	plane = init_plane(init_vector(max.x, min.y, max.z), vflip(dz), dy, mat);	// right
	append_obj(init_obj((void *)plane, PLANE, plane->mat));
	plane = init_plane(init_vector(max.x, min.y, min.z), vflip(dx), dy, mat);	// back
	append_obj(init_obj((void *)plane, PLANE, plane->mat));
	plane = init_plane(init_vector(min.x, min.y, min.z), dz, dy, mat);			// left
	append_obj(init_obj((void *)plane, PLANE, plane->mat));
	plane = init_plane(init_vector(min.x, max.y, max.z), dx, vflip(dz), mat);	// top
	append_obj(init_obj((void *)plane, PLANE, plane->mat));
	plane = init_plane(init_vector(min.x, min.y, min.z), dx, dz, mat);			// bottom
	append_obj(init_obj((void *)plane, PLANE, plane->mat));
}
