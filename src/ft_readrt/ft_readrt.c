/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readrt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:51:48 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/21 17:09:22 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readrt.h"

t_subrt	init_subrt(void)
{
	t_subrt	this;

	this = (t_subrt){
		.type = NOTHING,
		.value1 = 0.0,
		.value2 = 0.0,
		.ratio = 0.0,
		.point = init_vector(0.0, 0.0, 0.0),
		.color = init_vector(0.0, 0.0, 0.0),
		.vector = init_vector(0.0, 0.0, 0.0),
	};
	return (this);
}

t_dotrt	*single_rt(void)
{
	static t_dotrt	this;
	static int		is_init;

	if (is_init)
		return (&this);
	this = (t_dotrt){
		.a = init_subrt(),
		.c = init_subrt(),
		.l = init_subrt(),
		.sp = NULL,
		.pl = NULL,
		.cy = NULL,
		.cnt_sp = 0,
		.cnt_pl = 0,
		.cnt_cy = 0,
	};
	is_init = 1;
	return (&this);
}

t_dotrt	*new_rt(void)
{
	t_dotrt	*rt;
	int		i;

	rt = single_rt();
	i = 0;
	// TODO: implement configuring and producing new rt struct.
	return (rt);
}
