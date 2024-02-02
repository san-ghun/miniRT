/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:01:26 by sanghupa          #+#    #+#             */
/*   Updated: 2024/02/03 00:16:50 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_color(void);

int	key_hooks(int keycode, t_container *img)
{
	t_vars	*vars;
	t_temp	*temp;

	vars = single_vars();
	temp = single_temp();
	if (keycode == K_ESC)
		close_mlx(img);
	else if (keycode == K_SP)
		draw_square((t_square){0, 0, img->w, 0xFFFFFF}, img);
	else if (keycode == K_R)
		temp->color = get_color();
	else if (is_camera_position(keycode))
		adjust_camera_position(keycode);
	else if (is_camera_orientation(keycode))
		adjust_camera_orientation(keycode);
		
	mlx_put_image_to_window(vars->mlx, vars->win, img->img, 0, 0);
	return (0);
}

int	get_color(void)
{
	return (rand() % INT_MAX);
}
