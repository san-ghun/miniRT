/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:26:36 by sanghupa          #+#    #+#             */
/*   Updated: 2024/05/17 17:07:52 by minakim          ###   ########.fr       */
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
# include "ft_dotrt.h"

/*
** =============================================================================
** Macro
** =============================================================================
*/ 

# define N_SAMPLE	5
# define N_DEPTH	5
# define LUMEN		30
# define DISTANCE	5

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
	t_vec3		background;
	double		vfov;
	t_vec3		lookfrom;
	t_vec3		lookat;
	t_vec3		vup;
	double		defocus_angle;
	double		focus_dist;
	t_vec3		center;
	t_vec3		u;
	t_vec3		v;
	t_vec3		w;
	t_vec3		viewport_u;
	t_vec3		viewport_v;
	t_vec3		pixel_delta_u;
	t_vec3		pixel_delta_v;
	t_vec3		pixel00_loc;
	t_vec3		defocus_disk_u;
	t_vec3		defocus_disk_v;
}				t_camera;

/*
** =============================================================================
** Function
** =============================================================================
*/

// camera.c
t_camera	*single_cam(void);
t_camera	*init_camera(double aspect_ratio, int image_width);
void		setup_camera(int vfov, t_vec3 lookfrom, t_vec3 lookat, t_vec3 vup);
t_vec3		pixel_sample_square(t_camera *camera);
t_vec3		defocus_disk_sample(t_camera *camera);
// t_ray		get_ray(t_camera *camera, int i, int j);

// trace.c
t_vec3		ray_color(t_ray ray, int depth, t_obj *objs[]);

#endif
