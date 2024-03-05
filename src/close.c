/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 21:17:42 by sanghupa          #+#    #+#             */
/*   Updated: 2024/02/01 16:47:12 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_free_2d(void **targets)
{
	int	i;

	i = -1;
	while (targets[++i])
		free(targets[i]);
	free(targets);
	targets = NULL;
}

void	free_resource(t_resource *rsc)
{
	int	i;

	i = -1;
	while (rsc->mats[++i])
		free(rsc->mats[i]);
	i = -1;
	while (rsc->objs[++i])
	{
		if (rsc->objs[i]->texture != NULL)
			free(rsc->objs[i]->texture);
		free(rsc->objs[i]->data);
		free(rsc->objs[i]);
	}
	ft_bzero(rsc->mats, 100);
	ft_bzero(rsc->objs, 100);
	pthread_mutex_destroy(rsc->lock);
	free(rsc->lock);
	i = -1;
	while (++i < N_THREAD)
	{
		free(rsc->pths[i]->pth);
		free(rsc->pths[i]);
	}
	free(rsc->pths);
}

void	free_dotrt(t_dotrt *rt)
{
	int	i;

	i = -1;
	while (rt->sp[++i])
		free(rt->sp[i]);
	i = -1;
	while (rt->pl[++i])
		free(rt->pl[i]);
	i = -1;
	while (rt->cy[++i])
		free(rt->cy[i]);
	free(rt->a);
	free(rt->c);
	free(rt->l);
}

int	close_mlx(t_container *img)
{
	t_dotrt		*rt;
	t_vars		*vars;
	t_resource	*rsc;

	rt = single_rt();
	vars = single_vars();
	rsc = single_rsc();
	mlx_destroy_image(vars->mlx, img->img);
	mlx_destroy_window(vars->mlx, vars->win);

	/// NOT available in MacOS
	/// Un-comment following if you are compiling on Linux
	mlx_destroy_display(vars->mlx);

	free_resource(rsc);
	free(img);
	free(vars->mlx);
	free_dotrt(rt);
	exit(EXIT_SUCCESS);
}
