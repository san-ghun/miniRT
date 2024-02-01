/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:01:26 by sanghupa          #+#    #+#             */
/*   Updated: 2024/02/01 22:53:10 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/// @note tmp
# define DISTANCE	5

int	get_color(void);

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

void	camera_up(void)
{
	t_camera	*cam;
	t_vec3		new_lookfrom;
	
	cam = single_cam();
	
	new_lookfrom = init_vector(cam->lookfrom.x + (DISTANCE / 4), cam->lookfrom.y + DISTANCE, cam->lookfrom.z + (DISTANCE / 4));
//	new_lookfrom = init_vector(cam->lookfrom.x, cam->lookfrom.y + DISTANCE, cam->lookfrom.z);
	
	setup_camera(cam->vfov, new_lookfrom, cam->lookat, (t_vec3){0, 1, 0});
	debug_camera();
	render();
}

void	camera_down(void)
{
	t_camera	*cam;
	t_vec3		new_lookfrom;
	
	cam = single_cam();
	
	new_lookfrom = init_vector(cam->lookfrom.x, cam->lookfrom.y - DISTANCE, cam->lookfrom.z);
	setup_camera(cam->vfov, new_lookfrom, cam->lookat, (t_vec3){0, 1, 0});
	debug_camera();
	render();
}

void	camera_right(void)
{
	t_camera	*cam;
	t_vec3		new_lookfrom;
	
	cam = single_cam();
	
	new_lookfrom = init_vector(cam->lookfrom.x + DISTANCE, cam->lookfrom.y, cam->lookfrom.z);
	setup_camera(cam->vfov, new_lookfrom, cam->lookat, (t_vec3){0, 1, 0});
	debug_camera();
	render();
}

void	camera_left(void)
{
	t_camera	*cam;
	t_vec3		new_lookfrom;
//	t_vec3		new_lookat;
	
	cam = single_cam();
	
	new_lookfrom = init_vector(cam->lookfrom.x - DISTANCE, cam->lookfrom.y, cam->lookfrom.z);
	
//	new_lookfrom = init_vector(cam->lookfrom.x - DISTANCE, cam->lookfrom.y, cam->lookfrom.z + DISTANCE / 2 );
//	new_lookat = init_vector(cam->lookat.x - 10, cam->lookat.y, cam->lookat.z);
	setup_camera(cam->vfov, new_lookfrom, cam->lookat, (t_vec3){0, 1, 0});
	debug_camera();
	render();
}

void	camera_control(int keycode)
{
	else if (keycode == K_AR_U)
	{
		camera_up();
		printf("camera: up\n");
	}
	else if (keycode == K_AR_D)
	{
		camera_down();
		printf("camera: down\n");
	}
	else if (keycode == K_AR_R)
	{
		camera_right();
		printf("camera: right\n");
	}
	else if (keycode == K_AR_L)
	{
		camera_left();
		printf("camera: left\n");
	}
}

int	key_hooks(int keycode, t_container *img)
{
	t_vars	*vars;
	t_temp	*temp;

	vars = single_vars();
	temp = single_temp();
	if (keycode == K_ESC)
		close_mlx(img);
	else if (keycode == K_SP)
		draw_square((t_square){0, 0, img->w, 0xFFFFFF}, img);
	else if (keycode == K_R)
		temp->color = get_color();
	else if (keycode == K_AR_U)
	{
		camera_up();
		printf("camera: up\n");
	}
	else if (keycode == K_AR_D)
	{
		camera_down();
		printf("camera: down\n");
	}
	else if (keycode == K_AR_R)
	{
		camera_right();
		printf("camera: right\n");
	}
	else if (keycode == K_AR_L)
	{
		camera_left();
		printf("camera: left\n");
	}
	mlx_put_image_to_window(vars->mlx, vars->win, img->img, 0, 0);
	return (0);
}

int	get_color(void)
{
	return (rand() % INT_MAX);
}
