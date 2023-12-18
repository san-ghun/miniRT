/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:26:36 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/19 00:37:42 by sanghupa         ###   ########.fr       */
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
	double		aspect_ratio;		// Ratio of image width over height
	int			image_width;		// Rednered image width in pixel count
	int			image_height;		// Rendered image height
	int			samples_per_pixel;	// Count of random samples for each pixel
	int			max_depth;			// Maximum nuber of ray bounces into scene
	double		vfov;				// Vertical view angle (field of view)
	t_vec3		lookfrom;			// Point camera is looking from
	t_vec3		lookat;				// Point camera is looking at
	t_vec3		vup;				// Camera-relative "up" direction
	double		defocus_angle;		// Variation angle of rays through each pixel
	double		focus_dist;			// Distance from camera lookfrom point to plane of perfect focus
	t_vec3		center;				// Camera center
	t_vec3		pixel00_loc;		// Location of pixel 0, 0
	t_vec3		pixel_delta_u;		// Offset to pixel to the right
	t_vec3		pixel_delta_v;		// Offset to pixel below
	t_vec3		u;					// }
	t_vec3		v;					// } Camera frame basis vectors
	t_vec3		w;					// }
	t_vec3		defocus_disk_u;		// Defocus disk horizontal radius
	t_vec3		defocus_disk_v;		// Defocus disk vertical radius
}				t_camera;

/*
** =============================================================================
** Function
** =============================================================================
*/

t_camera	init_camera(double aspect_ratio, int image_width);
void		setup_camera(t_camera *this, int vfov, t_vec3 lookfrom, t_vec3 lookat, t_vec3 vup);
t_ray		get_ray(t_camera camera, int i, int j);
t_vec3		ray_color(t_ray ray, int depth, t_obj *objs[]);

#endif
