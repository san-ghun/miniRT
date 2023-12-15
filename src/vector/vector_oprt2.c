/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_oprt2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 16:44:26 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/11 00:29:05 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3	flip(t_vec3 v)
{
	return (scale(v, -1));
}

double	len_pow(t_vec3 v)
{
	return ((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

double	len_sqrt(t_vec3 v)
{
	return (sqrt(len_pow(v)));
}

t_vec3	unit(t_vec3 v)
{
	return (scale(v, (1.0 / len_sqrt(v))));
}

t_bool	near_zero(t_vec3 v)
{
	double	e;

	e = 1e-8;
	return ((fabs(v.x) < e) && (fabs(v.y) < e) && (fabs(v.z) < e));
}
