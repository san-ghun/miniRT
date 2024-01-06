/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 21:26:03 by minakim           #+#    #+#             */
/*   Updated: 2024/01/06 22:19:39 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dotrt.h"

t_bool	is_rgb(double color)
{
	if (color >= 0.0 && color <= 1.0)
		return (TRUE);
	return (FALSE);
}

t_bool	is_ratio(double num)
{
	if (num >= 0.0 && num <= 1.0)
		return (TRUE);
	return (FALSE);
}

t_bool	is_vector(double vector)
{
	if (vector >= -1.0 && vector <= 1.0)
		return (TRUE);
	return (FALSE);
}

t_bool	is_hov(double hov)
{
	if (hov >= 0 && hov <= 180)
		return (TRUE);
	return (FALSE);
}