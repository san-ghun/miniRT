/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 20:28:01 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/26 01:08:19 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"
#include <math.h>

void	rotate_obj_y(t_obj *obj, double angle)
{
	double	radians = angle * M_PI / 180.0;
	double	sin_theta = sin(radians);
	double	cos_theta = cos(radians);
	t_plane	*pl = (t_plane *)obj->data;
	t_aabb	bbox = pl->box;

	t_vec3	min = init_vector(INFINITY, INFINITY, INFINITY);
	t_vec3	max = init_vector(-INFINITY, -INFINITY, -INFINITY);

	int		i;
	int		j;
	int		k;
	double	x;
	double	y;
	double	z;
	t_vec3	tester;
	i = 0;
	while (i < 2)
	{
		while (j < 2)
		{
			while (k < 2)
			{
				x = i * bbox.x.max + (1 - i) * bbox.x.min;
				y = j * bbox.y.max + (1 - j) * bbox.y.min;
				z = k * bbox.z.max + (1 - k) * bbox.z.min;
				tester = init_vector(cos_theta * x + sin_theta * z, y, -sin_theta * x + cos_theta * z);
				min.x = fmin(min.x, tester.x);
				max.x = fmax(max.x, tester.x);
				min.y = fmin(min.y, tester.y);
				max.y = fmax(max.y, tester.y);
				min.z = fmin(min.z, tester.z);
				max.z = fmax(max.z, tester.z);
				k++;
			}
			j++;
		}
		i++;
	}
	pl->box = init_aabb_vec(min, max);
}
