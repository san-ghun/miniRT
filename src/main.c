/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:22:52 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/26 22:14:07 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	scene_zero(t_camera *cam);
void	light_one(t_camera *cam);
void	cornell_box(t_camera *cam);
void	box_one(t_camera *cam);

void	render(t_camera *camera, t_container *container)
{
	int		i;
	int		j;
	int		sample;
	t_ray	ray;
	t_vec3	col_v;
	double	scalev;
	int		color;

	j = 0;
	ft_printf("P3\n%d %d\n255\n", camera->image_width, camera->image_height);
	while (j < camera->image_height)
	{
		i = 0;
		while (i < camera->image_width)
		{
			col_v = init_vector(0.0, 0.0, 0.0);
			sample = 0;
			while (sample < camera->samples_per_pixel)
			{
				ray = get_ray(camera, i, j);
				col_v = vadd(col_v, ray_color(ray, camera->max_depth, single_rsc()->objs));
				sample++;
			}
			scalev = 1.0 / camera->samples_per_pixel;
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
	t_dotrt			*rt;
	t_camera		*cam;

	rt = new_rt();
	rt->a.ratio = 0.2;
	rt->a.color = init_vector(0.2, 0.2, 0.2);

	/// scene_zero
	// cam = init_camera(16.0 / 9.0, 400);
	// cam->samples_per_pixel = 10;
	// cam->max_depth = 10;

	/// light_one
	// cam = init_camera(16.0 / 9.0, 400);
	// cam->samples_per_pixel = 15;
	// cam->max_depth = 10;

	/// cornell_box
	// cam = init_camera(1.0, 600);
	// cam->samples_per_pixel = 50;
	// cam->max_depth = 10;

	/// box_one
	cam = init_camera(1.0, 400);
	cam->samples_per_pixel = 100;
	cam->max_depth = 20;

	(void)argc;
	(void)argv;
	/// init window
	vars = new_program(cam->image_width, cam->image_height, "New Program");
	if (!(vars->mlx) || !(vars->win))
		return (1);
	/// init image
	container = new_container(vars->width, vars->height, vars);

	// scene_zero(cam);
	// light_one(cam);
	// cornell_box(cam);
	box_one(cam);

	render(cam, container);

	mlx_put_image_to_window(vars->mlx, vars->win, container->img, 0, 0);

	/// hoooks
	mlx_hook(vars->win, 17, 0, close_mlx, container);
	mlx_key_hook(vars->win, key_hooks, container);
	mlx_mouse_hook(vars->win, mouse_hooks, container);
	mlx_loop(vars->mlx);

	return (0);
}

void	scene_zero(t_camera *cam)
{
	t_resource	*rsc;
	t_obj		*obj;
	t_sphere	*sphere;

	/// # Scene 0
	(void)rsc;
	rsc = new_resource();
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
				// j + 0.9 * ft_random(1, 2),
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

	cam->defocus_angle = 0.6;
	cam->focus_dist = 10.0;
	setup_camera(cam, 20, (t_vec3){13, 2, 3}, (t_vec3){0, 0, 0}, (t_vec3){0, 1, 0});
}

void	light_one(t_camera *cam)
{
	t_resource	*rsc;
	t_obj		*obj;
	t_sphere	*sphere;
	t_plane		*plane;

	/// # Light 1
	(void)rsc;
	rsc = new_resource();
	t_material	*mat_ground = init_material(0, init_vector(0.5, 0.5, 0.5), 0, 0);
	sphere = init_sphere(init_vector(0.0, -1000.0, 0.0), 1000.0, mat_ground);
	obj = init_obj((void *)sphere, SPHERE, mat_ground);
	append_obj(obj);
	t_material	*mat_center = init_material(0, init_vector(1.0, 0.2, 0.2), 0, 0);
	sphere = init_sphere(init_vector(0, 2, 0), 2.0, mat_center);
	obj = init_obj((void *)sphere, SPHERE, mat_center);
	append_obj(obj);
	t_material	*mat_light_sp = init_material(0, init_vector(0, 0, 0), 0, 0);
	mat_light_sp->emit_color = init_vector(4, 4, 4);
	sphere = init_sphere(init_vector(0, 7, 0), 2, mat_light_sp);
	obj = init_obj((void *)sphere, SPHERE, mat_light_sp);
	append_obj(obj);
	t_material	*mat_light_pl = init_material(0, init_vector(0, 0, 0), 0, 0);
	mat_light_pl->emit_color = init_vector(4, 4, 4);
	plane = init_plane(init_vector(3, 1, -2), init_vector(2, 0, 0), init_vector(0, 2, 0), mat_light_pl);
	obj = init_obj((void *)plane, PLANE, mat_light_pl);
	append_obj(obj);

	cam->background = init_vector(0, 0, 0);
	cam->defocus_angle = 0;
	setup_camera(cam, 20, init_vector(26, 3, 6), init_vector(0, 2, 0), init_vector(0, 1, 0));
}

void	cornell_box(t_camera *cam)
{
	t_resource	*rsc;
	t_obj		*obj;
	t_sphere	*sphere;
	t_plane		*plane;

	/// # Cornell Box
	(void)rsc;
	rsc = new_resource();
	t_material	*red = init_material(0, init_vector(0.65, 0.05, 0.05), 0, 0);
	t_material	*white0 = init_material(0, init_vector(0.73, 0.73, 0.73), 0, 0);
	t_material	*green = init_material(0, init_vector(0.12, 0.45, 0.15), 0, 0);
	t_material	*light = init_material(0, init_vector(0, 0, 0), 0, 0);
	light->emit_color = init_vector(15, 15, 15);
	append_mat(red, "red");
	append_mat(white0, "white0");
	append_mat(green, "green");
	append_mat(light, "light");
	plane = init_plane(init_vector(555, 0, 0), init_vector(0, 555, 0), init_vector(0, 0, 555), find_mat("green"));
	obj = init_obj((void *)plane, PLANE, plane->mat);
	append_obj(obj);
	plane = init_plane(init_vector(0, 0, 0), init_vector(0, 555, 0), init_vector(0, 0, 555), find_mat("red"));
	obj = init_obj((void *)plane, PLANE, plane->mat);
	append_obj(obj);
	plane = init_plane(init_vector(343, 554, 332), init_vector(-130, 0, 0), init_vector(0, 0, -105), find_mat("light"));
	// plane = init_plane(init_vector(113, 554, 127), init_vector(330, 0, 0), init_vector(0, 0, 305), find_mat("light"));
	plane->translate = init_vector(0, -100, 0);
	obj = init_obj((void *)plane, PLANE, plane->mat);
	append_obj(obj);
	plane = init_plane(init_vector(0, 0, 0), init_vector(555, 0, 0), init_vector(0, 0, 555), find_mat("white0"));
	obj = init_obj((void *)plane, PLANE, plane->mat);
	append_obj(obj);
	plane = init_plane(init_vector(555, 555, 555), init_vector(-555, 0, 0), init_vector(0, 0, -555), find_mat("white0"));
	obj = init_obj((void *)plane, PLANE, plane->mat);
	append_obj(obj);
	plane = init_plane(init_vector(0, 0, 555), init_vector(555, 0, 0), init_vector(0, 555, 0), find_mat("white0"));
	obj = init_obj((void *)plane, PLANE, plane->mat);
	append_obj(obj);
	// append_box(init_vector(130, 0, 65), init_vector(295, 165, 230), white0, -18, init_vector(0, 0, 0));
	append_box(init_vector(0, 0, 0), init_vector(165, 165, 165), white0, -18, init_vector(130, 0, 65));
	// append_box(init_vector(265, 0, 295), init_vector(430, 330, 460), white0, 15, init_vector(0, 0, 0));
	append_box(init_vector(0, 0, 0), init_vector(165, 330, 165), white0, 15, init_vector(265, 0, 295));
	// sphere = init_sphere(init_vector(425, 50, 80), 50.0, green);
	// obj = init_obj((void *)sphere, SPHERE, sphere->mat);
	// append_obj(obj);

	cam->background = init_vector(0, 0, 0);
	cam->defocus_angle = 0;
	setup_camera(cam, 40, init_vector(278, 278, -800), init_vector(278, 278, 0), init_vector(0, 1, 0));
}

void	box_one(t_camera *cam)
{
	t_resource	*rsc;
	t_obj		*obj;
	t_sphere	*sphere;
	t_plane		*plane;

	/// # Box 1
	(void)rsc;
	rsc = new_resource();
	t_material	*ground = init_material(0, init_vector(0.48, 0.83, 0.53), 0, 0);
	t_material	*light = init_material(0, init_vector(0, 0, 0), 0, 0);
	light->emit_color = init_vector(15, 15, 15);
	t_material	*solid = init_material(0, init_vector(0.7, 0.3, 0.1), 0, 0);
	t_material	*glass = init_material(2, init_vector(0, 0, 0), 0, 1.5);
	t_material	*metal = init_material(1, init_vector(0.8, 0.8, 0.9), 1.0, 0);
	t_material	*metal0 = init_material(1, init_vector(0.7, 0.6, 0.5), 0.0, 0);
	t_material	*white = init_material(0, init_vector(0.73, 0.73, 0.73), 0, 0);
	append_mat(ground, "ground");
	append_mat(light, "light");
	append_mat(solid, "solid");
	append_mat(glass, "glass");
	append_mat(metal, "metal");
	append_mat(metal0, "metal0");
	append_mat(white, "white");
	plane = init_plane(init_vector(-500, 70, -500), init_vector(1200, 0, 0), init_vector(0, 0, 1200), ground);
	obj = init_obj((void *)plane, PLANE, plane->mat);
	append_obj(obj);
	plane = init_plane(init_vector(123, 554, 147), init_vector(300, 0, 0), init_vector(0, 0, 265), find_mat("light"));
	obj = init_obj((void *)plane, PLANE, plane->mat);
	append_obj(obj);
	sphere = init_sphere(init_vector(400, 400, 200), 50, solid);
	obj = init_obj((void *)sphere, SPHERE, sphere->mat);
	append_obj(obj);
	sphere = init_sphere(init_vector(260, 150, 45), 50, glass);
	obj = init_obj((void *)sphere, SPHERE, sphere->mat);
	append_obj(obj);
	sphere = init_sphere(init_vector(360, 150, 145), 70, glass);
	obj = init_obj((void *)sphere, SPHERE, sphere->mat);
	append_obj(obj);
	sphere = init_sphere(init_vector(360, 150, 145), 69.8, solid);
	obj = init_obj((void *)sphere, SPHERE, sphere->mat);
	append_obj(obj);
	sphere = init_sphere(init_vector(0, 150, 145), 50, metal);
	obj = init_obj((void *)sphere, SPHERE, sphere->mat);
	append_obj(obj);
	sphere = init_sphere(init_vector(220, 280, 300), 80, metal0);
	obj = init_obj((void *)sphere, SPHERE, sphere->mat);
	append_obj(obj);
	append_box(init_vector(0, 0, 0), init_vector(165, 165, 165), white, 18, init_vector(-100, 270, 395));

	cam->background = init_vector(0, 0, 0);
	cam->defocus_angle = 0;
	setup_camera(cam, 40, init_vector(478, 278, -600), init_vector(278, 278, 0), init_vector(0, 1, 0));
}
