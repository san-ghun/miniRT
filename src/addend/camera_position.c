/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:01:50 by minakim           #+#    #+#             */
/*   Updated: 2024/02/05 21:02:03 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"

void	debug_camera(void)
{
	t_camera	*cam;
	
	cam = single_cam();
	printf("\n	[camera]\n");
	printf("Aspect Ratio: %f\n", cam->aspect_ratio);
	printf("Image Width: %d\n", cam->image_width);
	printf("Image Height: %d\n", cam->image_height);
	printf("Samples Per Pixel: %d\n", cam->samples_per_pixel);
	printf("Max Depth: %d\n", cam->max_depth);
	printf("Background Color: (%f, %f, %f)\n", cam->background.x, cam->background.y, cam->background.z);
	printf("Vertical FOV: %f\n", cam->vfov);
	printf("Look From: (%f, %f, %f)\n", cam->lookfrom.x, cam->lookfrom.y, cam->lookfrom.z);
	printf("Look At: (%f, %f, %f)\n", cam->lookat.x, cam->lookat.y, cam->lookat.z);
	printf("Vup: (%f, %f, %f)\n", cam->vup.x, cam->vup.y, cam->vup.z);
	printf("Defocus Angle: %f\n", cam->defocus_angle);
	printf("Focus Distance: %f\n", cam->focus_dist);
	printf("Center: (%f, %f, %f)\n", cam->center.x, cam->center.y, cam->center.z);
	printf("U: (%f, %f, %f)\n", cam->u.x, cam->u.y, cam->u.z);
	printf("V: (%f, %f, %f)\n", cam->v.x, cam->v.y, cam->v.z);
	printf("W: (%f, %f, %f)\n", cam->w.x, cam->w.y, cam->w.z);
	printf("Viewport U: (%f, %f, %f)\n", cam->viewport_u.x, cam->viewport_u.y, cam->viewport_u.z);
	printf("Viewport V: (%f, %f, %f)\n", cam->viewport_v.x, cam->viewport_v.y, cam->viewport_v.z);
	printf("Pixel Delta U: (%f, %f, %f)\n", cam->pixel_delta_u.x, cam->pixel_delta_u.y, cam->pixel_delta_u.z);
	printf("Pixel Delta V: (%f, %f, %f)\n", cam->pixel_delta_v.x, cam->pixel_delta_v.y, cam->pixel_delta_v.z);
	printf("Pixel 00 Location: (%f, %f, %f)\n", cam->pixel00_loc.x, cam->pixel00_loc.y, cam->pixel00_loc.z);
	printf("Defocus Disk U: (%f, %f, %f)\n", cam->defocus_disk_u.x, cam->defocus_disk_u.y, cam->defocus_disk_u.z);
	printf("Defocus Disk V: (%f, %f, %f)\n", cam->defocus_disk_v.x, cam->defocus_disk_v.y, cam->defocus_disk_v.z);
	printf("\n\n");
	
}

static t_c_addend	*linking_c_position(void)
{
	static t_c_addend 	this[] = {
			{K_AR_U, {0, DISTANCE, 0}, "up"},
			{K_AR_D, {0, -DISTANCE, 0}, "down"},
			{K_AR_R, {DISTANCE, 0, 0}, "right"},
			{K_AR_L, {-DISTANCE, 0, 0}, "left"},
			{K_NP_PLU, {0, 0, -DISTANCE}, "plus"},
			{K_NP_MIN, {0, 0, DISTANCE}, "minus"},
			{'\0', {0, 0, 0}, "NULL"}
	};
	static int		is_init;
	
	if (is_init)
		return (&(*this));
	is_init = TRUE;
	return (&(*this));
}

void	move_camera_lockfrom(t_vec3 param)
{
	t_camera	*cam;
	t_vec3		new_lookfrom;
	
	cam = single_cam();
	new_lookfrom = vadd(cam->lookfrom, param);
	setup_camera(cam->vfov, new_lookfrom, cam->lookat, (t_vec3){0, 1, 0});
	debug_camera();
	render();
}

void	adjust_camera_position(int keycode)
{
	t_c_addend 	*table;
	int		i;
	
	table = linking_c_position();
	i = -1;
	while (table[++i].keycode)
	{
		if (keycode == table[i].keycode)
		{
			move_camera_lockfrom(table[i].addend);
			printf("%s\n", table[i].name);
			return ;
		}
	}
}

t_bool	is_camera_position(int keycode)
{
	t_c_addend 	*table;
	int		i;
	
	table = linking_c_position();
	i = -1;
	while (table[++i].keycode)
	{
		if (keycode == table[i].keycode)
			return (TRUE);
	}
	return (FALSE);
}