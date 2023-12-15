/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:01:26 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/14 20:51:07 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	mouse_hooks(int button, int m_x, int m_y, t_container *img)
{
	t_vars	*vars;
	int		x;
	int		y;
	int		size;
	int		color;

	size = single_temp()->size;
	color = single_temp()->color;
	vars = single_vars();
	if (button == M_CLK_L)
	{
		if (m_x < 0 || m_y < 0 || m_x > img->w || m_y > img->h)
			return (2);
		x = ((m_x % img->w) / size) * size;
		y = ((m_y % img->h) / size) * size;
		draw_square((t_square){x, y, size, color}, img);
	}
	mlx_put_image_to_window(vars->mlx, vars->win, img->img, 0, 0);
	return (0);
}
