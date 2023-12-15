/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:15:54 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/15 20:34:15 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	put_pixel_data(t_container *cont, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < cont->w && y < cont->h)
	{
		dst = cont->addr + \
			(y * cont->line_length + x * (cont->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_square(t_square square, t_container *img)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	while (i < square.size && i + square.y < img->h)
	{
		j = 0;
		while (j < square.size && j + square.x < img->w)
		{
			color = square.color;
			get_trgb(1, get_r(color), get_g(color), get_b(color));
			put_pixel_data(img, j + square.x, i + square.y, color);
			j++;
		}
		i++;
	}
}

double	degree_to_radians(double degree)
{
	return (degree * M_PI / 180.0);
}

t_temp	*single_temp(void)
{
	static t_temp	this;
	static int		is_init;

	if (is_init)
		return (&this);
	this = (t_temp){
		.size = 10,
		.color = 0xFFFFFF,
		.counter = 0,
	};
	is_init = 1;
	return (&this);
}
