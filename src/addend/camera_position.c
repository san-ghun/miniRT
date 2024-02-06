/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:01:50 by minakim           #+#    #+#             */
/*   Updated: 2024/02/06 16:45:10 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_c_addend	*linking_c_position(void)
{
	static t_c_addend	this[] = {
	{K_AR_U, {0, DISTANCE, 0}, "up"},
	{K_AR_D, {0, -DISTANCE, 0}, "down"},
	{K_AR_L, {-DISTANCE, 0, 0}, "left"},
	{K_AR_R, {DISTANCE, 0, 0}, "right"},
	{K_NP_PLU, {0, 0, -DISTANCE}, "plus"},
	{K_NP_MIN, {0, 0, DISTANCE}, "minus"},
	{'\0', {0, 0, 0}, "NULL"}
	};
	static int			is_init;

	if (is_init)
		return (&(*this));
	is_init = TRUE;
	return (&(*this));
}

void	move_camera_lockfrom(t_vec3 param)
{
	t_camera	*cam;
	t_vec3		new_lookfrom;

	cam = single_cam();
	new_lookfrom = vadd(cam->lookfrom, param);
	setup_camera(cam->vfov, new_lookfrom, cam->lookat, (t_vec3){0, 1, 0});
	debug_camera();
	render();
}

void	adjust_camera_position(int keycode)
{
	t_c_addend	*table;
	int			i;

	table = linking_c_position();
	i = -1;
	while (table[++i].keycode)
	{
		if (keycode == table[i].keycode)
		{
			move_camera_lockfrom(table[i].addend);
			printf("> %s\n", table[i].name);
			return ;
		}
	}
}

t_bool	is_camera_position(int keycode)
{
	t_c_addend	*table;
	int			i;

	table = linking_c_position();
	i = -1;
	while (table[++i].keycode)
	{
		if (keycode == table[i].keycode)
			return (TRUE);
	}
	return (FALSE);
}
