/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readrt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:51:48 by sanghupa          #+#    #+#             */
/*   Updated: 2024/01/01 14:07:05 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dotrt.h"

t_subrt	*init_subrt(void)
{
	t_subrt	*this;

	this = malloc(sizeof(t_subrt) * 1);
	this->type = NOTHING;
	this->mat_type = 0;
	this->mat_value = 0.0;
	this->value1 = 0.0;
	this->value2 = 0.0;
	this->ratio = 0.0;
	this->point = init_vector(0.0, 0.0, 0.0);
	this->color = init_vector(0.0, 0.0, 0.0);
	this->vector = init_vector(0.0, 0.0, 0.0);
	this->vector2 = init_vector(0.0, 0.0, 0.0);
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
		.sp = {},
		.pl = {},
		.cy = {},
		.cnt_sp = 0,
		.cnt_pl = 0,
		.cnt_cy = 0,
	};
	ft_bzero(this.sp, 100);
	ft_bzero(this.pl, 100);
	ft_bzero(this.cy, 100);
	is_init = 1;
	return (&this);
}

t_dotrt	*new_rt(void)
{
	t_dotrt	*rt;
	int		i;

	rt = single_rt();
	i = 0;
	(void)i;
	// TODO: implement configuring and producing new rt struct.
	return (rt);
}
