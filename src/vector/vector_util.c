/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 00:40:18 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/29 20:53:50 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "ft_random.h"

t_vec3	vrandom(double min, double max)
{
	t_vec3	ret;

	ret = (t_vec3){
		ft_random(min, max), 
		ft_random(min, max), 
		ft_random(min, max)
	};
	return (ret);
}

t_vec3	vrandom_in_unit_sphere(void)
{
	t_vec3	p;

	while (1)
	{
		p = vrandom(-1, 1);
		if (vlen_sqrt(p) < 1)
			return (p);
	}
}

t_vec3	vrandom_unit_vector(void)
{
	return (vunit(vrandom_in_unit_sphere()));
}

t_vec3	vrandom_on_hemisphere(t_vec3 normal)
{
	t_vec3	on_unit_sphere;

	on_unit_sphere = vrandom_unit_vector();
	if (vdot(on_unit_sphere, normal) > 0.0)
		return (on_unit_sphere);
	else
		return (vflip(on_unit_sphere));
}

t_vec3	random_in_unit_disk(void)
{
	t_vec3	p;

	while (1)
	{
		p = init_vector(ft_random(-1, 1), ft_random(-1, 1), 0);
		if (vlen_sqrt(p) < 1)
			return (p);
	}
}
