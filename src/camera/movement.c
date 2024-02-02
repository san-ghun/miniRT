/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 23:22:49 by minakim           #+#    #+#             */
/*   Updated: 2024/02/03 00:39:49 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

# define	X	0
# define	Y	1
# define	Z	2

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

typedef struct s_c_p
{
	int		keycode;
	t_vec3 	param;
	char	name[20];
}			t_c_p;

static t_c_p	*linking_c_position(void)
{
	static t_c_p	this[] = {
			{K_AR_U, {0, DISTANCE, 0}, "up"},
			{K_AR_D, {0, -DISTANCE, 0}, "down"},
			{K_AR_R, {DISTANCE, 0, 0}, "right"},
			{K_AR_L, {-DISTANCE, 0, 0}, "left"},
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
	t_c_p	*table;
	int		i;
	
	table = linking_c_position();
	i = -1;
	while (table[++i].keycode)
	{
		if (keycode == table[i].keycode)
		{
			move_camera_lockfrom(table[i].param);
			printf("%s\n", table[i].name);
			return ;
		}
	}
}

t_bool	is_camera_position(int keycode)
{
	t_c_p	*table;
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

///////////////////////


void rotate_around_x(t_vec3 *vec, float angle)
{
	float cos_a = cos(angle);
	float sin_a = sin(angle);
	
	float new_y = vec->y * cos_a - vec->z * sin_a;
	float new_z = vec->y * sin_a + vec->z * cos_a;
	
	vec->y = new_y;
	vec->z = new_z;
}

void rotate_around_y(t_vec3 *vec, float angle)
{
	float cos_a = cos(angle);
	float sin_a = sin(angle);
	
	float new_x = vec->x * cos_a + vec->z * sin_a;
	float new_z = -vec->x * sin_a + vec->z * cos_a;
	
	vec->x = new_x;
	vec->z = new_z;
}

void rotate_around_z(t_vec3 *vec, float angle)
{
	float cos_a = cos(angle);
	float sin_a = sin(angle);
	
	float new_x = vec->x * cos_a - vec->y * sin_a;
	float new_y = vec->x * sin_a + vec->y * cos_a;
	
	vec->x = new_x;
	vec->y = new_y;
}

///////////////////////

void	move_camera_all(t_vec3 add_to_both)
{
	t_camera	*cam;
	t_vec3		new_lookfrom;
	t_vec3		new_lookat;
	
	cam = single_cam();
	new_lookfrom = vadd(cam->lookfrom, add_to_both);
	new_lookat = vadd(cam->lookat,add_to_both);
	setup_camera(cam->vfov, new_lookfrom, new_lookat, (t_vec3){0, 1, 0});
	debug_camera();
	render();
}

typedef struct s_c_o
{
	int		keycode;
	t_vec3	delta_looks;
	char	name[20];
}			t_c_o;

static t_c_o	*linking_c_orientation(void)
{
	static t_c_o	this[] = {
			{K_I, {0, DISTANCE, 0}, "up"},
			{K_K, {0, -DISTANCE, 0}, "down"},
			{K_J, {DISTANCE, 0, 0}, "right"},
			{K_L, {-DISTANCE, 0, 0}, "left"},
			{'\0', {0, 0, 0}, "NULL"}
	};
	static int		is_init;
	
	if (is_init)
		return (&(*this));
	is_init = TRUE;
	return (&(*this));
}

void	adjust_camera_orientation(int keycode)
{
	t_c_o	*table;
	int		i;
	
	table = linking_c_orientation();
	i = -1;
	while (table[++i].keycode)
	{
		if (keycode == table[i].keycode)
		{
//			float angle = table[i].delta_looks.x;
//			rotate_around_y(&table[i].delta_looks, angle);
			move_camera_all(table[i].delta_looks);
			printf("%s\n", table[i].name);
			return ;
		}
	}
}

t_bool	is_camera_orientation(int keycode)
{
	t_c_o	*table;
	int		i;
	
	table = linking_c_orientation();
	i = -1;
	while (table[++i].keycode)
	{
		if (keycode == table[i].keycode)
			return (TRUE);
	}
	return (FALSE);
}