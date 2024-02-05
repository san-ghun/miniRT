/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:01:26 by sanghupa          #+#    #+#             */
/*   Updated: 2024/02/05 20:42:11 by minakim          ###   ########.fr       */
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
	else if (is_camera_position(keycode)) /// re-located: lookfrom
		adjust_camera_position(keycode);
	else if (is_camera_orientation(keycode)) /// re-located: lookfrom, lookat
		adjust_camera_orientation(keycode);
	else if (is_objects(keycode))
		adjust_object(keycode);
	mlx_put_image_to_window(vars->mlx, vars->win, img->img, 0, 0);
	return (0);
}

int	get_color(void)
{
	return (rand() % INT_MAX);
}
