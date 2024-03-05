/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:17:47 by minakim           #+#    #+#             */
/*   Updated: 2024/03/05 17:18:56 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "args.h"

int	set_image_width(int width)
{
	int remainder;
	
	remainder = width % N_THREAD;
	if (remainder != 0)
		width += (N_THREAD - remainder);
	return (width);
}

t_mode	*single_mode(void)
{
	static t_mode	this;
	static int		is_init;
	
	if (is_init)
		return (&this);
	this = (t_mode) {
			.image_mode = FALSE,
			.image_index = -1,
			.image_width = set_image_width(1000),
			.ratio = 16.0 / 9.0,
			.debug_mode = FALSE,
			.debug_index = -1
	};
	is_init = 1;
	return (&this);
}
