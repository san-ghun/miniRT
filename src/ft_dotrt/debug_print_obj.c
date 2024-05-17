/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print_obj.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:36:48 by minakim           #+#    #+#             */
/*   Updated: 2024/05/17 16:37:30 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dotrt.h"
#include "args.h"

void	print_vec3(t_vec3 v)
{
	printf("{%.2f, %.2f, %.2f}", v.x, v.y, v.z);
}

void	print_sphere(t_subrt **sub, const char *object_type, int i)
{
	printf("Type: %s[%d], Point: ", object_type, i);
	print_vec3((*sub)->point);
	printf(", Diameter: %.2f, Color: ", (*sub)->value1);
	print_vec3((*sub)->color);
	printf("\n");
}

void	print_plane(t_subrt **sub, const char *object_type, int i)
{
	printf("Type: %s[%d], Point: ", object_type, i);
	print_vec3((*sub)->point);
	printf(", Vector: ");
	print_vec3((*sub)->vector);
	printf(", Color: ");
	print_vec3((*sub)->color);
	printf("\n");
}

void	print_cylinder(t_subrt **sub, const char *object_type, int i)
{
	printf("Type: %s[%d], Point: ", object_type, i);
	print_vec3((*sub)->point);
	printf(", Vector: ");
	print_vec3((*sub)->vector);
	printf(", Diameter: %.2f, Height: %.2f", (*sub)->value1, (*sub)->value2);
	printf(", Color: ");
	print_vec3((*sub)->color);
	printf("\n");
}

void	print_object_arr(
		t_subrt **objects, int count, const char *object_type)
{
	t_subrt	*sub;
	int		i;

	i = -1;
	while (++i < count)
	{
		sub = objects[i];
		if (sub == NULL)
			return ;
		if (sub->type == SPHERE)
			print_sphere(&sub, object_type, i);
		else if (sub->type == PLANE)
			print_plane(&sub, object_type, i);
		else if (sub->type == CYLINDER)
			print_cylinder(&sub, object_type, i);
		else
			printf("Type: %s invalid\n", object_type);
	}
}
