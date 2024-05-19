/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 16:18:49 by minakim           #+#    #+#             */
/*   Updated: 2024/05/17 16:15:53 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dotrt.h"

int	verify_cylinder_element(char **array, int index)
{
	double	diameter;
	double	height;

	diameter = ft_stod(array[CY_DIAMETER]);
	if (isnan(diameter) || !is_unit(diameter))
		return (error_invalid_element(CYLINDER, index));
	height = ft_stod(array[CY_HEIGHT]);
	if (isnan(height) || !is_unit(height))
		return (error_invalid_element(CYLINDER, index));
	return (VALID);
}

int	verify_cylinder_tuple(char **a, char ***point, char ***vector, char ***rgb)
{
	t_dotrt	*rt;

	rt = single_rt();
	*point = ft_split(a[CY_POINT], ',');
	if (valid_tuple(*point, CYLINDER, rt->cnt_cy, NULL) != VALID)
		return (INVALID);
	*vector = ft_split(a[CY_VECTOR], ',');
	if (valid_tuple(*vector, CYLINDER, rt->cnt_cy, is_vector) != VALID)
		return (ft_arr_free(*point), INVALID);
	*rgb = ft_split(a[CY_RGB], ',');
	if (valid_tuple(*rgb, CYLINDER, rt->cnt_cy, is_rgb) != VALID)
	{
		ft_arr_free(*point);
		ft_arr_free(*vector);
		return (INVALID);
	}
	return (VALID);
}

void	set_rt_cylinder(char **a, char **point, char **vector, char **rgb)
{
	t_dotrt	*rt;
	t_subrt	*sub;

	rt = single_rt();
	sub = init_subrt();
	sub->type = CYLINDER;
	sub->point = set_tuple(point);
	sub->vector = set_tuple(vector);
	sub->value1 = ft_stod(a[CY_DIAMETER]);
	sub->value2 = ft_stod(a[CY_HEIGHT]);
	sub->color = set_rgb(rgb);
	rt->cy[rt->cnt_cy] = sub;
	rt->cnt_cy++;
}

int	as_cylinder(char **array)
{
	t_dotrt	*rt;
	char	**point;
	char	**vector;
	char	**rgb;

	rt = single_rt();
	if (array_len(array) != 6)
		return (error_invalid_element(CYLINDER, rt->cnt_cy));
	if (verify_cylinder_element(array, rt->cnt_cy))
		return (INVALID);
	if (verify_cylinder_tuple(array, &point, &vector, &rgb) != VALID)
		return (INVALID);
	set_rt_cylinder(array, point, vector, rgb);
	return (VALID);
}
