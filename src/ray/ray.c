/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:28:34 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/11 00:31:44 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_ray	init_ray(t_vec3 origin, t_vec3 direction)
{
	t_ray	this;

	this.origin = origin;
	this.direction = direction;
	return (this);
}

t_vec3	ray_at(t_ray r, double t)
{
	return (add(r.origin, scale(r.direction, t)));
}
