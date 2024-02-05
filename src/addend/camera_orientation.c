/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:25:27 by minakim           #+#    #+#             */
/*   Updated: 2024/02/05 21:48:49 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	move_camera_all(t_vec3 add_to_both)
{
	t_camera	*cam;
	t_vec3		new_lookfrom;
	t_vec3		new_lookat;

	cam = single_cam();
	new_lookfrom = vadd(cam->lookfrom, add_to_both);
	new_lookat = vadd(cam->lookat, add_to_both);
	setup_camera(cam->vfov, new_lookfrom, new_lookat, (t_vec3){0, 1, 0});
	debug_camera();
	render();
}

static t_c_addend	*linking_c_orientation(void)
{
	static t_c_addend	this[] = {
	{K_I, {0, DISTANCE, 0}, "up"},
	{K_K, {0, -DISTANCE, 0}, "down"},
	{K_L, {DISTANCE, 0, 0}, "right"},
	{K_J, {-DISTANCE, 0, 0}, "left"},
	{K_SP, {0, 0, 0}, "reset"},
	{'\0', {0, 0, 0}, "NULL"}
	};
	static int			is_init;

	if (is_init)
		return (&(*this));
	is_init = TRUE;
	return (&(*this));
}

void	rollback_camera(void)
{
	t_camera	*cam;
	t_dotrt		*rt;

	rt = single_rt();
	cam = single_cam();
	cam->samples_per_pixel = N_SAMPLE;
	cam->max_depth = N_DEPTH;
	cam->background = init_vector(0, 0, 0);
	cam->defocus_angle = 0.0;
	cam->focus_dist = 10.0;
	setup_camera(rt->c->value1, rt->c->point, rt->c->vector, (t_vec3){0, 1, 0});
	debug_camera();
	render();
}

void	adjust_camera_orientation(int keycode)
{
	t_c_addend	*table;
	int			i;

	table = linking_c_orientation();
	i = -1;
	while (table[++i].keycode)
	{
		if (keycode == table[i].keycode)
		{
			if (keycode == K_SP)
				rollback_camera();
			else
				move_camera_all(table[i].addend);
			printf("%s\n", table[i].name);
			return ;
		}
	}
}

t_bool	is_camera_orientation(int keycode)
{
	t_c_addend	*table;
	int			i;

	table = linking_c_orientation();
	i = -1;
	while (table[++i].keycode)
	{
		if (keycode == table[i].keycode)
			return (TRUE);
	}
	return (FALSE);
}
