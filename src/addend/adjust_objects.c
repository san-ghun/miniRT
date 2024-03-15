/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:18:46 by minakim           #+#    #+#             */
/*   Updated: 2024/03/13 18:42:18 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	init_keycode_connect(t_aes *this)
{
	this[0] = (t_aes){K_R, PLANE, {DISTANCE, 0, 0}, "pl: right"};
	this[1] = (t_aes){K_Q, PLANE, {-DISTANCE, 0, 0}, "pl: left"};
	this[2] = (t_aes){K_W, PLANE, {0, DISTANCE, 0}, "pl: up"};
	this[3] = (t_aes){K_E, PLANE, {0, -DISTANCE, 0}, "pl: down"};
	this[4] = (t_aes){K_T, PLANE, {0, 0, DISTANCE}, "pl: adding depth"};
	this[5] = (t_aes){K_Y, PLANE, {0, 0, -DISTANCE}, "pl: reducing depth"};
	this[6] = (t_aes){K_F, SPHERE, {DISTANCE, 0, 0}, "sp: right"};
	this[7] = (t_aes){K_A, SPHERE, {-DISTANCE, 0, 0}, "sp: left"};
	this[8] = (t_aes){K_S, SPHERE, {0, DISTANCE, 0}, "sp: up"};
	this[9] = (t_aes){K_D, SPHERE, {0, -DISTANCE, 0}, "sp: down"};
	this[10] = (t_aes){K_G, SPHERE, {0, 0, DISTANCE}, "sp: adding depth"};
	this[11] = (t_aes){K_H, SPHERE, {0, 0, -DISTANCE}, "sp: reducing depth"};
	this[12] = (t_aes){K_V, CYLINDER, {DISTANCE, 0, 0}, "cy: right"};
	this[13] = (t_aes){K_Z, CYLINDER, {-DISTANCE, 0, 0}, "cy: left"};
	this[14] = (t_aes){K_X, CYLINDER, {0, DISTANCE, 0}, "cy: up"};
	this[15] = (t_aes){K_C, CYLINDER, {0, -DISTANCE, 0}, "cy: down"};
	this[16] = (t_aes){K_B, CYLINDER, {0, 0, DISTANCE}, "cy: adding depth"};
	this[17] = (t_aes){K_N, CYLINDER, {0, 0, -DISTANCE}, "cy: reducing depth"};
}

static t_aes	*linking_objects(void)
{
	static t_aes	this[18];
	static int		is_init;

	if (is_init)
		return (&(*this));
	is_init = TRUE;
	init_keycode_connect(this);
	return (&(*this));
}

void	find_obj_and_addend(t_aes addend)
{
	t_resource	*rsc;
	int			i;

	rsc = single_rsc();
	i = -1;
	while (rsc->objs[++i])
	{
		if (rsc->objs[i]->type == addend.type)
			set_point_with_addend(rsc->objs[i], addend);
	}
	render();
}

void	adjust_object(int keycode)
{
	t_aes	*table;
	int		i;

	table = linking_objects();
	i = -1;
	while (table[++i].keycode)
	{
		if (keycode == table[i].keycode)
		{
			if (table[i].type == PLANE || table[i].type == SPHERE \
				|| table[i].type == CYLINDER)
			{
				print_prompt_object(table[i].name);
				find_obj_and_addend(table[i]);
			}
			return ;
		}
	}
}

t_bool	is_objects(int keycode)
{
	t_aes	*table;
	int		i;

	table = linking_objects();
	i = -1;
	while (table[++i].keycode)
	{
		if (keycode == table[i].keycode)
			return (TRUE);
	}
	return (FALSE);
}
