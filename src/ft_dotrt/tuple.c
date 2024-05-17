/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 16:06:17 by minakim           #+#    #+#             */
/*   Updated: 2024/01/08 22:04:50 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dotrt.h"

/// This function validates a tuple, t_vec3, consisting of x,y,z.
///	It converts each *ele of the array to a double, via ft_stod,
/// and verifies that it is nan.
/// \param ele it divided by ft_split, has x,y,z as string.
/// \param id a target object's name, identifier.
/// \param i total number of the target object
/// \param is_range is a function pointer,
/// which takes in the is_format.c functions that verify the correct range
/// for each element.
/// If f_range is NULL, the range of the element is not checked.
/// \return valid/invalid
int	valid_tuple(char **ele, int id, int i, f_range is_range)
{
	double	val;
	int		j;

	j = -1;
	if (!ele || !*ele)
		return (INVALID);
	if (array_len(ele) != 3)
	{
		ft_arr_free(ele);
		return (error_invalid_element(id, i));
	}
	while (ele[++j])
	{
		val = ft_stod(ele[j]);
		if (isnan(val))
			return (ft_arr_free(ele), error_invalid_element(id, i));
		if (is_range != NULL && !is_range(val))
			return (ft_arr_free(ele), error_wrong_range(id, i));
	}
	return (VALID);
}

/// @warning these three functions below have no checks to validate parameters,
/// and assume that all previous checks have been completed.
t_vec3	set_tuple(char **v)
{
	t_vec3	target;

	target = (t_vec3){ft_stod(v[0]), ft_stod(v[1]), ft_stod(v[2])};
	ft_arr_free(v);
	return (target);
}

double	rgb_conv(char *s)
{
	double	res;

	res = 0.0;
	res = ft_stod(s);
	return (res / 255.0);
}

t_vec3	set_rgb(char **rgb)
{
	t_vec3	this;

	this = (t_vec3){rgb_conv(rgb[0]), rgb_conv(rgb[1]), rgb_conv(rgb[2])};
	ft_arr_free(rgb);
	return (this);
}
