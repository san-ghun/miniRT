/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:57:57 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/24 11:03:13 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vars	*new_program(int w, int h, char *str)
{
	t_vars	*vars;

	vars = single_vars();
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, w, h, str);
	vars->width = w;
	vars->height = h;
	return (vars);
}

t_container	*new_container(int w, int h, t_vars *vars)
{
	t_container	*this;

	this = (t_container *)malloc(sizeof(t_container));
	this->img = mlx_new_image(vars->mlx, w, h);
	this->addr = mlx_get_data_addr(\
		this->img, &(this->bits_per_pixel), \
		&(this->line_length), &(this->endian));
	this->w = w;
	this->h = h;
	return (this);
}

t_resource	*new_resource(void)
{
	t_resource	*rsc;

	rsc = single_rsc();
	// rsc->objs = malloc(sizeof(t_obj *) * (n_obj + 1));
	// i = 0;
	// while (i < n_obj + 1)
	// {
	// 	rsc->objs[i] = NULL;
	// 	i++;
	// }
	ft_bzero(rsc->objs, 100);
	rsc->len_objs = 0;
	return (rsc);
}
