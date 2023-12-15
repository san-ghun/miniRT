/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_oprt1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 16:44:26 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/16 00:14:40 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3	vadd(t_vec3 u, t_vec3 v)
{
	return (init_vector((u.x + v.x), (u.y + v.y), (u.z + v.z)));
}

t_vec3	vsubtract(t_vec3 u, t_vec3 v)
{
	return (init_vector((u.x - v.x), (u.y - v.y), (u.z - v.z)));
}

t_vec3	vscale(t_vec3 v, double s)
{
	return (init_vector((v.x * s), (v.y * s), (v.z * s)));
}

double	vdot(t_vec3 u, t_vec3 v)
{
	return ((u.x * v.x) + (u.y * v.y) + (u.z * v.z));
}

t_vec3	vcross(t_vec3 u, t_vec3 v)
{
	t_vec3	t;

	t.x = u.y * v.z - u.z * v.y;
	t.y = u.z * v.x - u.x * v.z;
	t.z = u.x * v.y - u.y * v.x;
	return (t);
}
