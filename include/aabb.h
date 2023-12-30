/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 23:25:16 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/29 21:06:09 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Axis-Aligned Bounding Boxes (AABBs)
#ifndef AABB_H
# define AABB_H

/*
** =============================================================================
** Dependency
** =============================================================================
*/

# include "vector.h"
# include "ray.h"
# include "interval.h"

/*
** =============================================================================
** Type Definition
** =============================================================================
*/

typedef int		t_bool;

typedef struct s_aabb
{
	t_interval	x;
	t_interval	y;
	t_interval	z;
}				t_aabb;

/*
** =============================================================================
** Function
** =============================================================================
*/

t_aabb		init_aabb_itv(t_interval ix, t_interval iy, t_interval iz);
t_aabb		init_aabb_vec(t_vec3 a, t_vec3 b);
// t_aabb		init_aabb_box(t_aabb box0, t_aabb box1);
t_interval	aabb_axis(t_aabb box, int n);
t_bool		aabb_hit(t_aabb box, t_ray ray, t_interval ray_t);
t_aabb		aabb_pad(t_aabb box);

#endif
