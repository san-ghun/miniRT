/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interval.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:00:23 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/22 00:55:26 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interval.h"
#include <math.h>

t_interval	init_interval(double min, double max)
{
	t_interval	this;

	this.min = min;
	this.max = max;
	return (this);
}

t_interval	init_interval_itv(t_interval a, t_interval b)
{
	t_interval	this;

	this = (t_interval){
		.min = fmin(a.min, b.min),
		.max = fmax(a.max, b.max),
	};
	return (this);
}

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
