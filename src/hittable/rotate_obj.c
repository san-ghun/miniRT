/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 23:21:52 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/29 23:31:23 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"

void	pre_rotate(t_ray *ray, double radians)
{
	double	sin_theta;
	double	cos_theta;
	t_vec3	origin;
	t_vec3	direction;

	sin_theta = sin(radians);
	cos_theta = cos(radians);
	origin = ray->origin;
	direction = ray->direction;
	origin.x = cos_theta * ray->origin.x - sin_theta * ray->origin.z;
	origin.z = sin_theta * ray->origin.x + cos_theta * ray->origin.z;
	direction.x = cos_theta * ray->direction.x - sin_theta * ray->direction.z;
	direction.z = sin_theta * ray->direction.x + cos_theta * ray->direction.z;
	ray->origin = origin;
	ray->direction = direction;
}

void	post_rotate(t_hit *rec, double radians)
{
	double	sin_theta;
	double	cos_theta;
	t_vec3	point;
	t_vec3	normal;

	sin_theta = sin(radians);
	cos_theta = cos(radians);
	point = rec->point;
	normal = rec->normal;
	point.x = cos_theta * rec->point.x + sin_theta * rec->point.z;
	point.z = -sin_theta * rec->point.x + cos_theta * rec->point.z;
	normal.x = cos_theta * rec->normal.x + sin_theta * rec->normal.z;
	normal.z = -sin_theta * rec->normal.x + cos_theta * rec->normal.z;
	rec->point = point;
	rec->normal = normal;
}
