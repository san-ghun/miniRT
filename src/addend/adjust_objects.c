/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:18:46 by minakim           #+#    #+#             */
/*   Updated: 2024/02/05 21:20:00 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_addends	*linking_objects(void)
{
	static t_addends	this[18] = {
			{K_R, PLANE, {DISTANCE, 0, 0}, "pl: right"},
			{K_Q, PLANE, {-DISTANCE, 0, 0}, "pl: left"},
			{K_W, PLANE, {0, DISTANCE, 0}, "pl: up"},
			{K_E, PLANE, {0, -DISTANCE, 0}, "pl: down"},
			{K_T, PLANE, {0, 0, DISTANCE}, "pl: adding depth"},
			{K_Y, PLANE, {0, 0, -DISTANCE}, "pl: reducing depth"},
			{K_F, SPHERE, {DISTANCE, 0, 0}, "sp: right"},
			{K_A, SPHERE, {-DISTANCE, 0, 0}, "sp: left"},
			{K_S, SPHERE, {0, DISTANCE, 0}, "sp: up"},
			{K_D, SPHERE, {0, -DISTANCE, 0}, "sp: down"},
			{K_G, SPHERE, {0, 0, DISTANCE}, "sp: adding depth"},
			{K_H, SPHERE, {0, 0, -DISTANCE}, "sp: reducing depth"},
			{K_V, CYLINDER, {DISTANCE, 0, 0}, "cy: right"},
			{K_Z, CYLINDER, {-DISTANCE, 0, 0}, "cy: left"},
			{K_X, CYLINDER, {0, DISTANCE, 0}, "cy: up"},
			{K_C, CYLINDER, {0, -DISTANCE, 0}, "cy: down"},
			{K_B, CYLINDER, {0, 0, DISTANCE}, "cy: adding depth"},
			{K_N, CYLINDER, {0, 0, -DISTANCE}, "cy: reducing depth"},
	};
	static int		is_init;
	
	if (is_init)
		return (&(*this));
	is_init = TRUE;
	return (&(*this));
}

void	set_point_with_addend(t_obj *obj, t_addends addend)
{
	if (addend.type == PLANE)
		obj->data = (void *)pl_add_position((t_plane *)obj->data, addend);
	else if (addend.type == SPHERE)
		obj->data = (void *)sp_add_position((t_sphere *)obj->data, addend);
	else if (addend.type == CYLINDER)
		obj->data = (void *)cy_add_position((t_cylinder *)obj->data, addend);
	return ;
}

void	find_obj_and_addend(t_addends addend)
{
	t_resource	*rsc;
	int			i;
	
	rsc = single_rsc();
	i = -1;
	while (rsc->objs[++i])
	{
		if (rsc->objs[i]->type == addend.type)
		{
			set_point_with_addend(rsc->objs[i], addend);
		}
	}
	render();
}

void	adjust_object(int keycode)
{
	t_addends	*table;
	int			i;
	
	table = linking_objects();
	i = -1;
	while (table[++i].keycode)
	{
		if (keycode == table[i].keycode)
		{
			if (table[i].type == PLANE || table[i].type == SPHERE || table[i].type == CYLINDER)
			{
				find_obj_and_addend(table[i]);
				printf("%s\n", table[i].name);
			}
			return ;
		}
	}
}

t_bool	is_objects(int keycode)
{
	t_addends 	*table;
	int			i;
	
	table = linking_objects();
	i = -1;
	while (table[++i].keycode)
	{
		if (keycode == table[i].keycode)
			return (TRUE);
	}
	return (FALSE);
}