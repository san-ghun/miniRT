/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:22:20 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/15 16:25:06 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_random.h"

int	ft_randint(void)
{
	static int	seed;

	seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
	return (seed);
}

double	ft_randdouble(void)
{
	static int	seed;

	seed = (seed * 1103515245 + 12345) & 0x7fffffff;
	return ((double)seed / (double)0x80000000);
}

double	ft_random(double min, double max)
{
	return ((ft_randdouble() * (max - min)) + min);
}
