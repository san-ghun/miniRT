/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 14:29:37 by minakim           #+#    #+#             */
/*   Updated: 2024/05/17 16:46:33 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dotrt.h"
#include "args.h"

void	print_ambient(t_subrt **sub)
{
	if ((*sub)->type == AMBIENT)
	{
		printf("Type: AMBIENT, Ratio: %.2f, Color: ", (*sub)->ratio);
		print_vec3((*sub)->color);
		printf("\n");
	}
	else
		printf("Type: AMBIENT invalid\n");
}

void	print_camera(t_subrt **sub)
{
	if ((*sub)->type == CAMERA)
	{
		printf("Type: CAMERA, Point: ");
		print_vec3((*sub)->point);
		printf(", Vector: ");
		print_vec3((*sub)->vector);
		printf(", Value1: %.2f\n", (*sub)->value1);
	}
	else
		printf("Type: CAMERA invalid\n");
}

void	print_light(t_subrt **sub)
{
	if ((*sub)->type == LIGHT)
	{
		printf("Type: LIGHT, Point: ");
		print_vec3((*sub)->point);
		printf(", Ratio: %.2f, Color: ", (*sub)->ratio);
		print_vec3((*sub)->color);
		printf("\n");
	}
	else
		printf("Type: LIGHT invalid\n");
}

void	print_objects(t_dotrt **rt)
{
	print_object_arr((*rt)->sp, (*rt)->cnt_sp, "SPHERE");
	print_object_arr((*rt)->pl, (*rt)->cnt_pl, "PLANE");
	print_object_arr((*rt)->cy, (*rt)->cnt_cy, "CYLINDER");
}

void	print_rt(void)
{
	t_dotrt	*rt;
	t_subrt	*sub;
	t_mode	*mode;

	mode = single_mode();
	if (mode->debug_mode != TRUE)
		return ;
	printf("-----------------------------------------------------------\n");
	printf("dot rt file\n");
	printf("-----------------------------------------------------------\n");
	rt = single_rt();
	sub = rt->a;
	print_ambient(&sub);
	sub = rt->c;
	print_camera(&sub);
	sub = rt->l;
	print_light(&sub);
	print_objects(&rt);
	printf("\n\n\t\t\t--finish print output the .rt file --\n\n\n");
}
