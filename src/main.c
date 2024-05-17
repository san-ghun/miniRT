/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:22:52 by sanghupa          #+#    #+#             */
/*   Updated: 2024/05/08 15:11:22 by minakim          ###   ########.fr       */
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
	setup_camera(rt->c->value1, rt->c->point, rt->c->vector, \
	(t_vec3){0, 1, 0});
	return (cam);
}

static void	mlx_run(t_vars *vars, t_container *container)
{
	mlx_put_image_to_window(vars->mlx, vars->win, container->img, \
	0, 0);
	mlx_hook(vars->win, 17, 0, close_mlx, container);
	mlx_key_hook(vars->win, key_hooks, container);
	mlx_loop(vars->mlx);
}

void print_menu(void)
{
	printf("|-------------------------------------------------------------------------------------------|\n");
	printf("  Menu:\n");
	printf("  1. Move sphere: Q[left], W[up], E[down], R[right], T[adding depth], Y[reducing depth]\n");
	printf("  2. Move cylinder: A[left], S[up], D[down], F[right], G[adding depth], H[reducing depth]\n");
	printf("  3. Move planer: Z[left], X[up], C[down], V[right], V[adding depth], B[reducing depth]\n");
	printf("  4. Camera type 1 rotation: Up, Down, Left, Right\n");
	printf("  5. Camera type 2 move camera: J[left], I[up], K[down], L[right]\n");
	printf("|-------------------------------------------------------------------------------------------|\n");
}


int	main(int argc, char *argv[])
{
	t_vars			*vars;
	t_container		*container;
	t_camera		*cam;
	t_dotrt			*rt;
	t_resource		*rsc;

	if (!args_check(argc, argv))
		return (EXIT_FAILURE);
	rsc = new_resource();
	rt = read_rt(argv[rsc->mode->rt_index]);
	if (rt == NULL)
		return (free_resource(rsc), free_dotrt(single_rt()), EXIT_FAILURE);
	apply_dotrt(rt);
	cam = init_camera(rsc->mode->ratio, rsc->mode->image_width);
	cam = cam_ready(cam, rt);
	vars = new_program(cam->image_width, cam->image_height, "miniRT");
	if (!(vars->mlx) || !(vars->win))
		return (EXIT_FAILURE);
	container = vars->container;
	render();
	print_menu();
	mlx_run(vars, container);
	return (EXIT_SUCCESS);
}
