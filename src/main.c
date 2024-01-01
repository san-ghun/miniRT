/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:22:52 by sanghupa          #+#    #+#             */
/*   Updated: 2024/01/01 13:01:32 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_camera	*cam_ready(t_camera *cam, t_dotrt *rt)
{
	cam->samples_per_pixel = N_SAMPLE;
	cam->max_depth = N_DEPTH;
	cam->background = init_vector(0, 0, 0);
	cam->defocus_angle = 0.0;
	cam->focus_dist = 10.0;
	setup_camera(rt->c->value1, rt->c->point, rt->c->vector, (t_vec3){0, 1, 0});
	return (cam);
}

static void	mlx_run(t_vars *vars, t_container *container)
{
	mlx_put_image_to_window(vars->mlx, vars->win, container->img, 0, 0);
	mlx_hook(vars->win, 17, 0, close_mlx, container);
	mlx_key_hook(vars->win, key_hooks, container);
	mlx_mouse_hook(vars->win, mouse_hooks, container);
	mlx_loop(vars->mlx);
}

int	main(int argc, char *argv[])
{
	t_vars			*vars;
	t_container		*container;
	t_dotrt			*rt;
	t_camera		*cam;
	t_resource		*rsc;

	rsc = new_resource();
	(void)rsc;
	rt = new_rt();
	set_dotrt(rt);
	apply_dotrt(rt);
	cam = init_camera(16.0 / 9.0, 400);
	cam = cam_ready(cam, rt);
	(void)argc;
	(void)argv;
	vars = new_program(cam->image_width, cam->image_height, "New Program");
	if (!(vars->mlx) || !(vars->win))
		return (1);
	container = vars->container;
	render();
	mlx_run(vars, container);
	return (0);
}
