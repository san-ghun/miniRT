/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 19:14:48 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/24 20:28:45 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"

void	translate_obj(t_obj *obj, t_vec3 offset)
{
	t_sphere	*prev_sp;
	t_sphere	*new_sp;
	t_plane		*prev_pl;
	t_plane		*new_pl;

	if (obj->type == SPHERE)
	{
		prev_sp = (t_sphere *)obj->data;
		new_sp = init_sphere(\
			vadd(prev_sp->center, offset), \
			prev_sp->radius, prev_sp->mat);
		obj->data = (void *)new_sp;
		free(prev_sp);
	}
	if (obj->type == PLANE)
	{
		prev_pl = (t_plane *)obj->data;
		// new_pl = init_plane(\
			vadd(prev_pl->point, offset), \
			vadd(prev_pl->u, offset), \
			vadd(prev_pl->v, offset), \
			prev_pl->mat);
		new_pl = init_plane(\
			vadd(prev_pl->point, offset), prev_pl->u, prev_pl->v, prev_pl->mat);
		obj->data = (void *)new_pl;
		free(prev_pl);
	}
	return ;
}
