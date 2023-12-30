/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 22:06:25 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/29 22:40:57 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include <math.h>

static double	degrees_to_radians(double degrees)
{
	return (degrees * M_PI / 180.0);
}

static void	setup_viewport_dimensions(t_camera *this)
{
	double	focal_len;
	double	h;
	double	viewport_h;
	double	viewport_w;

	focal_len = vlen_pow(vsubtract(this->lookfrom, this->lookat));
	(void)focal_len;
	h = tan(degrees_to_radians(this->vfov) / 2);
	viewport_h = 2.0 * h * this->focus_dist;
	viewport_w = viewport_h * this->aspect_ratio;
	this->viewport_u = vscale(this->u, viewport_w);
	this->viewport_v = vscale(vflip(this->v), viewport_h);
}

static void	calculate_upper_left(t_camera *this)
{
	t_vec3	viewport_upper_left;

	viewport_upper_left = vsubtract(this->center, \
									vscale(this->w, this->focus_dist));
	viewport_upper_left = vsubtract(viewport_upper_left, \
									vscale(this->viewport_u, 0.5));
	viewport_upper_left = vsubtract(viewport_upper_left, \
									vscale(this->viewport_v, 0.5));
	this->pixel00_loc = (t_vec3){
		viewport_upper_left.x + 0.5 * \
			(this->pixel_delta_u.x + this->pixel_delta_v.x),
		viewport_upper_left.y + 0.5 * \
			(this->pixel_delta_u.y + this->pixel_delta_v.y),
		viewport_upper_left.z + 0.5 * \
			(this->pixel_delta_u.z + this->pixel_delta_v.z),
	};
}

void	setup_camera(int vfov, t_vec3 lookfrom, t_vec3 lookat, t_vec3 vup)
{
	t_camera	*this;
	double		defocus_radius;

	this = single_cam();
	this->vfov = vfov;
	this->lookfrom = lookfrom;
	this->lookat = lookat;
	this->vup = vup;
	this->center = this->lookfrom;
	this->w = vunit(vsubtract(this->lookfrom, this->lookat));
	this->u = vunit(vcross(this->vup, this->w));
	this->v = vcross(this->w, this->u);
	setup_viewport_dimensions(this);
	this->pixel_delta_u = vscale(this->viewport_u, 1.0 / this->image_width);
	this->pixel_delta_v = vscale(this->viewport_v, 1.0 / this->image_height);
	calculate_upper_left(this);
	defocus_radius = this->focus_dist * \
					tan(degrees_to_radians(this->defocus_angle / 2));
	this->defocus_disk_u = vscale(this->u, defocus_radius);
	this->defocus_disk_v = vscale(this->v, defocus_radius);
	return ;
}
