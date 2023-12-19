/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:22:52 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/19 02:08:22 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	render(t_camera camera, t_container *container)
{
	int		i;
	int		j;
	int		sample;
	t_ray	ray;
	t_vec3	col_v;
	double	scalev;
	int		color;

	j = 0;
	ft_printf("P3\n%d %d\n255\n", camera.image_width, camera.image_height);
	while (j < camera.image_height)
	{
		i = 0;
		while (i < camera.image_width)
		{
			col_v = init_vector(0.0, 0.0, 0.0);
			sample = 0;
			while (sample < camera.samples_per_pixel)
			{
				ray = get_ray(camera, i, j);
				col_v = vadd(col_v, ray_color(ray, camera.max_depth, single_rsc()->objs));
				sample++;
			}
			scalev = 1.0 / camera.samples_per_pixel;
			col_v = vscale(col_v, scalev);
			col_v = get_rgb(col_v.x, col_v.y, col_v.z);
			write_color(col_v);
			color = get_trgb(0, (int)col_v.x, (int)col_v.y, (int)col_v.z);
			put_pixel_data(container, i, j, color);
			i++;
		}
		j++;
	}
}

int	main(int argc, char *argv[])
{
	t_vars			*vars;
	t_container		*container;
	t_resource		*rsc;
	t_camera		cam;

	double	aspect_ratio = 16.0 / 9.0;
	int		image_w = 400;
	cam = init_camera(aspect_ratio, image_w);
	cam.samples_per_pixel = 10;
	cam.max_depth = 10;

	cam.defocus_angle = 0.6;
	cam.focus_dist = 10.0;

	setup_camera(&cam, 20, (t_vec3){13, 2, 3}, (t_vec3){0, 0, 0}, (t_vec3){0, 1, 0});

	(void)rsc;
	t_obj		*obj;
	t_sphere	*sphere;

	/// # Scene 0
	rsc = new_resource(40);
	t_material	*mat_ground = init_material(0, init_vector(0.5, 0.5, 0.5), 0, 0);
	sphere = init_sphere(init_vector(0.0, -1000.0, 0.0), 1000.0, mat_ground);
	obj = init_obj((void *)sphere, SPHERE, mat_ground);
	append_obj(obj);

	int	j = -3;
	while (++j < 4)
	{
		int i = -3;
		while (++i < 4)
		{
			double	choose_mat = ft_randdouble();
			t_vec3	center = (t_vec3){
				j + 0.9 * ft_randdouble(),
				0.2,
				i + 0.9 * ft_randdouble(),
				};
			if (vlen_pow(vsubtract(center, init_vector(4, 0.2, 0))) > 0.9)
			{
				t_material	*temp_mat;
				if (choose_mat < 0.8)
				{
					t_vec3	albedo = vmult(vrandom(0, 1), vrandom(0, 1));
					temp_mat = init_material(0, albedo, 0, 0);
					sphere = init_sphere(center, 0.2, temp_mat);
					obj = init_obj((void *)sphere, SPHERE, temp_mat);
					append_obj(obj);
				}
				else if (choose_mat < 0.95)
				{
					t_vec3	albedo = vrandom(0.5, 1);
					double	fuzz = ft_random(0, 0.5);
					temp_mat = init_material(1, albedo, fuzz, 0);
					sphere = init_sphere(center, 0.2, temp_mat);
					obj = init_obj((void *)sphere, SPHERE, temp_mat);
					append_obj(obj);
				}
				else
				{
					temp_mat = init_material(2, init_vector(0, 0, 0), 0, 1.5);
					sphere = init_sphere(center, 0.2, temp_mat);
					obj = init_obj((void *)sphere, SPHERE, temp_mat);
					append_obj(obj);
				}
			}
		}
	}
	t_material	*mat_center = init_material(2, init_vector(0.0, 0.0, 0.0), 0, 1.5);
	sphere = init_sphere(init_vector(0, 1, 0), 1.0, mat_center);
	obj = init_obj((void *)sphere, SPHERE, mat_center);
	append_obj(obj);
	t_material	*mat_left = init_material(0, init_vector(0.4, 0.2, 0.1), 0, 0);
	sphere = init_sphere(init_vector(-4, 1, 0), 1.0, mat_left);
	obj = init_obj((void *)sphere, SPHERE, mat_left);
	append_obj(obj);
	t_material	*mat_right = init_material(1, init_vector(0.7, 0.6, 0.5), 0, 0.0);
	sphere = init_sphere(init_vector(4, 1, 0), 1.0, mat_right);
	obj = init_obj((void *)sphere, SPHERE, mat_right);
	append_obj(obj);

	/// # Scene 1
	// rsc = new_resource(5);
	// t_material	*mat_ground = init_material(0, init_vector(0.8, 0.8, 0.0), 0, 0);
	// t_material	*mat_center = init_material(0, init_vector(0.1, 0.2, 0.5), 0, 0);
	// t_material	*mat_left = init_material(2, init_vector(0.0, 0.0, 0.0), 0, 1.5);
	// t_material	*mat_right = init_material(1, init_vector(0.8, 0.6, 0.2), 0.0, 0);
	// sphere = init_sphere(init_vector(0.0, -100.5, -1.0), 100.0, mat_ground);
	// obj = init_obj((void *)sphere, SPHERE, mat_ground);
	// append_obj(obj);
	// sphere = init_sphere(init_vector(0.0, 0.0, -1.0), 0.5, mat_center);
	// obj = init_obj((void *)sphere, SPHERE, mat_center);
	// append_obj(obj);
	// sphere = init_sphere(init_vector(-1.0, 0.0, -1.0), 0.5, mat_left);
	// obj = init_obj((void *)sphere, SPHERE, mat_left);
	// append_obj(obj);
	// sphere = init_sphere(init_vector(-1.0, 0.0, -1.0), -0.4, mat_left);
	// obj = init_obj((void *)sphere, SPHERE, mat_left);
	// append_obj(obj);
	// sphere = init_sphere(init_vector(1.0, 0.0, -1.0), 0.5, mat_right);
	// obj = init_obj((void *)sphere, SPHERE, mat_right);
	// append_obj(obj);

	/// # Scene 2
	// double	R = cos(M_PI / 4);
	// rsc = new_resource(2);
	// t_material	*mat_left = init_material(0, init_vector(0.0, 0.0, 1.0), 0.0, 0);
	// t_material	*mat_right = init_material(0, init_vector(1.0, 0.0, 0.0), 0.0, 0);
	// sphere = init_sphere(init_vector(-R, 0.0, -1.0), R, mat_left);
	// obj = init_obj((void *)sphere, SPHERE, mat_left);
	// append_obj(obj);
	// sphere = init_sphere(init_vector(R, 0.0, -1.0), R, mat_right);
	// obj = init_obj((void *)sphere, SPHERE, mat_right);
	// append_obj(obj);

	(void)argc;
	(void)argv;
	/// init window
	vars = new_program(cam.image_width, cam.image_height, "New Program");
	if (!(vars->mlx) || !(vars->win))
		return (1);
	/// init image
	container = new_container(vars->width, vars->height, vars);

	render(cam, container);

	mlx_put_image_to_window(vars->mlx, vars->win, container->img, 0, 0);

	/// hoooks
	mlx_hook(vars->win, 17, 0, close_mlx, container);
	mlx_key_hook(vars->win, key_hooks, container);
	mlx_mouse_hook(vars->win, mouse_hooks, container);
	mlx_loop(vars->mlx);

	return (0);
}
