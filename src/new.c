/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:57:57 by sanghupa          #+#    #+#             */
/*   Updated: 2024/03/05 14:44:59 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_thread	*new_thread(size_t id)
{
	t_thread	*this;

	this = malloc(sizeof(t_thread) * 1);
	this->id = id;
	this->pth = malloc(sizeof(pthread_t) * 1);
	return (this);
}

t_resource	*new_resource(void)
{
	t_resource	*rsc;
	int			i;

	rsc = single_rsc();
	ft_bzero(rsc->objs, 100);
	ft_bzero(rsc->mats, 100);
	rsc->len_objs = 0;
	rsc->len_mats = 0;
	rsc->pths = malloc(sizeof(t_thread *) * N_THREAD);
	ft_bzero(rsc->pths, N_THREAD);
	rsc->lock = malloc(sizeof(t_mux) * 1);
	pthread_mutex_init(rsc->lock, NULL);
	i = -1;
	while (++i < N_THREAD)
		rsc->pths[i] = new_thread(i);
	rsc->mode = single_mode();
	return (rsc);
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

t_vars	*new_program(int w, int h, char *str)
{
	t_vars	*vars;

	vars = single_vars();
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, w, h, str);
	vars->width = w;
	vars->height = h;
	vars->container = new_container(w, h, vars);
	return (vars);
}
