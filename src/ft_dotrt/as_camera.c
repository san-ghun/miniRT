/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_camera.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 16:17:30 by minakim           #+#    #+#             */
/*   Updated: 2024/01/07 17:45:02 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dotrt.h"

int	verify_camera_element(char **array, char ***point, char ***vector, int obj_n)
{
	double	fov;
	
	fov = ft_stod(array[C_FOV]);
	if (isnan(fov) || !is_hov(fov))
		return (error_invalid_element(CAMERA, obj_n));
	*point = ft_split(array[C_VIEWPOINT], ',');
	if (valid_tuple(*point, CAMERA, obj_n, NULL) != VALID)
		return (INVALID);
	*vector = ft_split(array[C_VECTOR], ',');
	if (valid_tuple(*vector, CAMERA, obj_n, is_vector) != VALID)
		return (ft_arr_free(*point), INVALID);
	return (VALID);
}

void	set_rt_camera(char **view_point, char **vector, char *fov)
{
	t_dotrt		*rt;
	
	rt = single_rt();
	rt->c->type = CAMERA;
	rt->c->point = set_tuple(view_point);
	rt->c->vector = set_tuple(vector);
	rt->c->value1 = ft_stod(fov);
}

int	as_camera(char **array)
{
	char	**view_point;
	char	**vector;
	static int	obj_n = 0;
	
	view_point = NULL;
	vector = NULL;
	if (++obj_n > 1)
		return (error_invalid_element(CAMERA, obj_n));
	if (array_len(array) != 4)
		return (error_invalid_element(CAMERA, obj_n));
	if (verify_camera_element(array, &view_point, &vector, obj_n) != VALID)
		return (INVALID);
	set_rt_camera(view_point, vector, array[C_FOV]);
	return (VALID);
}