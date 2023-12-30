/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interval.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:00:23 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/29 21:21:38 by sanghupa         ###   ########.fr       */
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
