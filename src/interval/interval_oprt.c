/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interval_oprt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 21:21:47 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/29 21:21:57 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interval.h"
#include <math.h>

t_bool	contains(t_interval interval, double x)
{
	return (interval.min <= x && x <= interval.max);
}

t_bool	surrounds(t_interval interval, double x)
{
	return (interval.min < x && x < interval.max);
}

double	clamp(t_interval interval, double x)
{
	if (x < interval.min)
		return (interval.min);
	if (x > interval.max)
		return (interval.max);
	return (x);
}

t_interval	expand_interval(t_interval itv, double delta)
{
	double	padding;

	padding = delta / 2;
	return (init_interval(itv.min - padding, itv.max + padding));
}

double	size_itv(t_interval itv)
{
	return (itv.max - itv.min);
}
