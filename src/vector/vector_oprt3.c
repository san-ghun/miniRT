/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_oprt3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 14:32:33 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/18 13:56:15 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3	vmult(t_vec3 vec, t_vec3 vec2)
{
	vec.x *= vec2.x;
	vec.y *= vec2.y;
	vec.z *= vec2.z;
	return (vec);
}

t_vec3	vreflect(t_vec3 v, t_vec3 n)
{
	t_vec3	ret;

	ret = vscale(n, 2 * vdot(v, n));
	ret = vsubtract(v, ret);
	return (ret);
}

t_vec3	vrefract(t_vec3 uv, t_vec3 n, double etai_over_etat)
{
	double	cos_theta;
	t_vec3	r_out_perp;
	t_vec3	r_out_parallel;

	cos_theta = fmin(vdot(vflip(uv), n), 1.0);
	r_out_perp = vscale(vadd(uv, vscale(n, cos_theta)), etai_over_etat);
	r_out_parallel = vscale(n, -sqrt(fabs(1.0 - vlen_pow(r_out_perp))));
	return (vadd(r_out_perp, r_out_parallel));
}
