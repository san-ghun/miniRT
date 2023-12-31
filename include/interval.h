/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interval.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:53:45 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/22 00:06:01 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERVAL_H
# define INTERVAL_H

/*
** =============================================================================
** Dependency
** =============================================================================
*/

/*
** =============================================================================
** Type Definition
** =============================================================================
*/

typedef int		t_bool;

typedef struct s_interval
{
	double		min;
	double		max;
}				t_interval;

/*
** =============================================================================
** Function
** =============================================================================
*/

t_interval	init_interval(double min, double max);
t_interval	init_interval_itv(t_interval a, t_interval b);
t_bool		contains(t_interval interval, double x);
t_bool		surrounds(t_interval interval, double x);
double		clamp(t_interval interval, double x);
t_interval	expand_interval(t_interval itv, double delta);
double		size_itv(t_interval itv);

#endif
