/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 16:18:23 by minakim           #+#    #+#             */
/*   Updated: 2024/01/07 16:40:22 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dotrt.h"

void	set_rt_sphere(char **point, char **rgb, char *diameter)
{
	t_dotrt	*rt;
	t_subrt	*sub;

	rt = single_rt();
	sub = init_subrt();
	sub->type = SPHERE;
	sub->point = set_tuple(point);
	sub->value1 = ft_stod(diameter) / 2;
	sub->color = set_rgb(rgb);
	rt->sp[rt->cnt_sp] = sub;
	rt->cnt_sp++;
}

int	verify_sphere_element(char **array, char ***point, char ***rgb, int index)
{
	double	diameter;

	diameter = ft_stod(array[SP_DIAMETER]);
	if (isnan(diameter) || !is_unit(diameter))
		return (error_invalid_element(SPHERE, index));
	*point = ft_split(array[SP_POINT], ',');
	if (valid_tuple(*point, SPHERE, index, NULL) != VALID)
		return (INVALID);
	*rgb = ft_split(array[SP_RGB], ',');
	if (valid_tuple(*rgb, SPHERE, index, is_rgb) != VALID)
		return (ft_arr_free(*point), INVALID);
	return (VALID);
}

int	as_sphere(char **array)
{
	t_dotrt	*rt;
	char	**point;
	char	**rgb;

	rt = single_rt();
	if (array_len(array) != 4)
		return (error_invalid_element(SPHERE, rt->cnt_sp));
	if (verify_sphere_element(array, &point, &rgb, rt->cnt_sp) != VALID)
		return (INVALID);
	set_rt_sphere(point, rgb, array[SP_DIAMETER]);
	return (VALID);
}
