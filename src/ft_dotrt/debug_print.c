/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 14:29:37 by minakim           #+#    #+#             */
/*   Updated: 2024/01/07 17:44:46 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dotrt.h"
#include <stdio.h> /// FIXME: printf used

void	print_vec3(t_vec3 v)
{
	printf("{%.2f, %.2f, %.2f}", v.x, v.y, v.z);
}

void	print_object_array(t_subrt **objects, int count, const char *object_type)
{
	t_subrt *sub;
	
	for (int i = 0; i < count; ++i)
	{
		sub = objects[i];
		if (sub == NULL)
			return ;
		if (sub->type == SPHERE)
		{
			printf("Type: %s[%d], Point: ", object_type, i);
			print_vec3(sub->point);
			printf(", Diameter: %.2f, Color: ", sub->value1);
			print_vec3(sub->color);
			printf("\n");
		}
		else if (sub->type == PLANE)
		{
			printf("Type: %s[%d], Point: ", object_type, i);
			print_vec3(sub->point);
			printf(", Vector: ");
			print_vec3(sub->vector);
			printf(", Color: ");
			print_vec3(sub->color);
			printf("\n");
		}
		else if (sub->type == CYLINDER)
		{
			printf("Type: %s[%d], Point: ", object_type, i);
			print_vec3(sub->point);
			printf(", Vector: ");
			print_vec3(sub->vector);
			printf(", Diameter: %.2f, Height: %.2f", sub->value1, sub->value2);
			printf(", Color: ");
			print_vec3(sub->color);
			printf("\n");
		}
		else
			printf("Type: %s invalid\n", object_type);
	}
}

void	print_rt(void)
{
	t_dotrt	*rt;
	t_subrt	*sub;
	
	rt = single_rt();
	printf("**Please clear or command out this file before submitting.\n");
	printf("ft_dotrt/debug_print.c\n");
	printf("warning: This file uses printf (a prohibited function) to print double val.\n");
	printf("\n\n");
	sub = rt->a;
	if (sub->type == AMBIENT)
	{
		printf("Type: AMBIENT, Ratio: %.2f, Color: ", sub->ratio);
		print_vec3(sub->color);
		printf("\n");
	}
	else
		printf("Type: AMBIENT invalid\n");
	///
	sub = rt->c;
	if (sub->type == CAMERA)
	{
		printf("Type: CAMERA, Point: ");
		print_vec3(sub->point);
		printf(", Vector: ");
		print_vec3(sub->vector);
		printf(", Value1: %.2f\n", sub->value1);
	}
	else
		printf("Type: CAMERA invalid\n");
	///
	sub = rt->l;
	if (sub->type == LIGHT)
	{
		printf("Type: LIGHT, Point: ");
		print_vec3(sub->point);
		printf(", Ratio: %.2f, Color: ", sub->ratio);
		print_vec3(sub->color);
		printf("\n");
	}
	else
		printf("Type: LIGHT invalid\n");
	///
	print_object_array(rt->sp, rt->cnt_sp, "SPHERE");
	print_object_array(rt->pl, rt->cnt_pl, "PLANE");
	print_object_array(rt->cy, rt->cnt_cy, "CYLINDER");
	///
	printf("\n\n\t\t\t--finish print output the .rt file --\n\n\n");
}