/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 21:17:42 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/24 17:53:04 by sanghupa         ###   ########.fr       */
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

int	close_mlx(t_container *img)
{
	t_vars		*vars;
	t_resource	*rsc;
	int			i;

	vars = single_vars();
	rsc = single_rsc();
	mlx_destroy_image(vars->mlx, img->img);
	mlx_destroy_window(vars->mlx, vars->win);

	/// NOT available in MacOS
	/// Un-comment following if you are compiling on Linux
	// mlx_destroy_display(vars->mlx);

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
	// free(rsc->objs);
	// rsc->objs = NULL;
	ft_bzero(rsc->mats, 100);
	ft_bzero(rsc->objs, 100);
	free(img);
	free(vars->mlx);
	exit(EXIT_SUCCESS);
}
