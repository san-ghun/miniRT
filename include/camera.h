/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:26:36 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/18 14:10:13 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

/*
** =============================================================================
** Dependency
** =============================================================================
*/

# include "vector.h"
# include "ray.h"
# include "hittable.h"
# include "color.h"
# include "ft_random.h"

/*
** =============================================================================
** Type Definition
** =============================================================================
*/

typedef int		t_bool;

typedef struct s_camera
{
	double		aspect_ratio;
	int			image_width;
	int			image_height;
	int			samples_per_pixel;
	int			max_depth;
	double		vfov;
	t_vec3		center;
	t_vec3		pixel00_loc;	// Location of pixel 0, 0
	t_vec3		pixel_delta_u;	// Offset to pixel to the right
	t_vec3		pixel_delta_v;	// Offset to pixel below
}				t_camera;

/*
** =============================================================================
** Function
** =============================================================================
*/

t_camera	init_camera(double aspect_ratio, int image_width);
t_ray		get_ray(t_camera camera, int i, int j);
t_vec3		ray_color(t_ray ray, int depth, t_obj *objs[]);

#endif
