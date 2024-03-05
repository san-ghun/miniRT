/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:15:09 by minakim           #+#    #+#             */
/*   Updated: 2024/03/05 19:53:26 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "addend.h"

t_bool	vecequ(t_vec3 a, t_vec3 b)
{
	if (a.x == b.x && a.y == b.y && a.z == b.z)
		return (TRUE);
	return (FALSE);
}

t_vec3	nonset(void)
{
	return (init_vector(0, 0, 0));
}

void	moremore(void)
{
	t_camera	*c;

	c = single_cam();
	printf("\n	[camera]\n");
	printf("Aspect Ratio: %f\n", c->aspect_ratio);
	printf("Image Width: %d\n", c->image_width);
	printf("Image Height: %d\n", c->image_height);
	printf("Samples Per Pixel: %d\n", c->samples_per_pixel);
	printf("Max Depth: %d\n", c->max_depth);
	printf("Background Color: (%f, %f, %f)\n", \
		c->background.x, c->background.y, c->background.z);
	printf("Vertical FOV: %f\n", c->vfov);
	printf("Look From: (%f, %f, %f)\n", \
		c->lookfrom.x, c->lookfrom.y, c->lookfrom.z);
	printf("Look At: (%f, %f, %f)\n", c->lookat.x, c->lookat.y, c->lookat.z);
	printf("Vup: (%f, %f, %f)\n", c->vup.x, c->vup.y, c->vup.z);
	printf("Defocus Angle: %f\n", c->defocus_angle);
	printf("Focus Distance: %f\n", c->focus_dist);
}

void	debug_camera(void)
{
	t_camera	*c;
	t_mode		*mode;
	
	mode = single_mode();
	if (mode->debug_mode != TRUE)
		return ;
	c = single_cam();
	moremore();
	printf("Center: (%f, %f, %f)\n", c->center.x, c->center.y, c->center.z);
	printf("U: (%f, %f, %f)\n", c->u.x, c->u.y, c->u.z);
	printf("V: (%f, %f, %f)\n", c->v.x, c->v.y, c->v.z);
	printf("W: (%f, %f, %f)\n", c->w.x, c->w.y, c->w.z);
	printf("Viewport U: (%f, %f, %f)\n", \
		c->viewport_u.x, c->viewport_u.y, c->viewport_u.z);
	printf("Viewport V: (%f, %f, %f)\n", \
	c->viewport_v.x, c->viewport_v.y, c->viewport_v.z);
	printf("Pixel Delta U: (%f, %f, %f)\n", \
		c->pixel_delta_u.x, c->pixel_delta_u.y, c->pixel_delta_u.z);
	printf("Pixel Delta V: (%f, %f, %f)\n", \
		c->pixel_delta_v.x, c->pixel_delta_v.y, c->pixel_delta_v.z);
	printf("Pixel 00 Location: (%f, %f, %f)\n", \
		c->pixel00_loc.x, c->pixel00_loc.y, c->pixel00_loc.z);
	printf("Defocus Disk U: (%f, %f, %f)\n", \
		c->defocus_disk_u.x, c->defocus_disk_u.y, c->defocus_disk_u.z);
	printf("Defocus Disk V: (%f, %f, %f)\n", \
		c->defocus_disk_v.x, c->defocus_disk_v.y, c->defocus_disk_v.z);
	printf("\n\n");
}
