/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 21:33:01 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/27 22:20:00 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vars	*single_vars(void)
{
	static t_vars	this;
	static int		is_init;

	if (is_init)
		return (&this);
	this = (t_vars){
		.mlx = NULL,
		.win = NULL,
		.width = 0,
		.height = 0,
		.container = NULL,
	};
	is_init = 1;
	return (&this);
}

t_resource	*single_rsc(void)
{
	static t_resource	this;
	static int			is_init;

	if (is_init)
		return (&this);
	this = (t_resource){
		.objs = {},
		.mats = {},
		.len_objs = 0,
		.len_mats = 0,
		.pths = NULL,
		.lock = NULL,
	};
	is_init = 1;
	return (&this);
}
