/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_rt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 16:12:55 by minakim           #+#    #+#             */
/*   Updated: 2024/01/07 17:44:07 by minakim          ###   ########.fr       */
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
	ft_bzero(this.sp, MAX_SUBRT);
	ft_bzero(this.pl, MAX_SUBRT);
	ft_bzero(this.cy, MAX_SUBRT);
	is_init = 1;
	return (&this);
}
