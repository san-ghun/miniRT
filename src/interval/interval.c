/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interval.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:00:23 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/15 17:57:23 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interval.h"

t_interval	init_interval(double min, double max)
{
	t_interval	this;

	this.min = min;
	this.max = max;
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
