/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:01:26 by sanghupa          #+#    #+#             */
/*   Updated: 2024/05/17 15:47:30 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_color(void);

int	key_hooks(int keycode, t_container *img)
{
	t_vars	*vars;

	vars = single_vars();
	if (keycode == K_ESC)
		close_mlx(img);
	else if (is_camera_position(keycode))
		adjust_camera_position(keycode);
	else if (is_camera_orientation(keycode))
		adjust_camera_orientation(keycode);
	else if (is_objects(keycode))
		adjust_object(keycode);
	mlx_put_image_to_window(vars->mlx, vars->win, img->img, 0, 0);
	return (0);
}
