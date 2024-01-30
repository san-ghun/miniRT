/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:01:26 by sanghupa          #+#    #+#             */
/*   Updated: 2024/01/30 18:43:11 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_color(void);

void	camera_up(t_vars *vars, t_container *img)
{
	t_camera	*cam;
	cam = single_cam();
	cam->lookfrom. // <<
	
	mlx_destroy_image(vars->mlx, img->img);
	render();
}

void	camera_down(void);
void	camera_right(void);
void	camera_left(void);

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
	else if (keycode == K_AR_U)
	{
		if (temp->size < img->w / 4)
			temp->size++;
	}
	else if (keycode == K_AR_D)
	{
		if (temp->size > 10)
			temp->size--;
	}
	else if (keycode == K_W)
	{
		camera_up(vars, img);
		printf("w\n");
	}
	mlx_put_image_to_window(vars->mlx, vars->win, img->img, 0, 0);
	return (0);
}

int	get_color(void)
{
	return (rand() % INT_MAX);
}
