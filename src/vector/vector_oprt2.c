/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_oprt2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 16:44:26 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/16 00:15:17 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3	vflip(t_vec3 v)
{
	return (vscale(v, -1));
}

double	vlen_pow(t_vec3 v)
{
	return ((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

double	vlen_sqrt(t_vec3 v)
{
	return (sqrt(vlen_pow(v)));
}

t_vec3	vunit(t_vec3 v)
{
	return (vscale(v, (1.0 / vlen_sqrt(v))));
}

t_bool	vnear_zero(t_vec3 v)
{
	double	e;

	e = 1e-8;
	return ((fabs(v.x) < e) && (fabs(v.y) < e) && (fabs(v.z) < e));
}
