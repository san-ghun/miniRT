/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:56:55 by minakim           #+#    #+#             */
/*   Updated: 2024/01/30 18:00:50 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	set_image_width(int width)
{
	int remainder;
	
	remainder = width % N_THREAD;
	if (remainder != 0)
		width += (N_THREAD - remainder);
	return (width);
}