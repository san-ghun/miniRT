/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_light.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 16:17:47 by minakim           #+#    #+#             */
/*   Updated: 2024/01/07 16:20:46 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dotrt.h"

int	verify_light_element(char **array, char ***point, char ***rgb, int obj_n)
{
	double	ratio;

	ratio = ft_stod(array[L_RATIO]);
	if (isnan(ratio) || !is_ratio(ratio))
		return (error_invalid_element(LIGHT, obj_n));
	*point = ft_split(array[L_POINT], ',');
	if (valid_tuple(*point, LIGHT, obj_n, NULL) != VALID)
		return (INVALID);
	*rgb = ft_split(array[L_RGB], ',');
	if (valid_tuple(*rgb, LIGHT, obj_n, is_rgb) != VALID)
		return (ft_arr_free(*point), INVALID);
	return (VALID);
}

void	set_rt_light(char **light_point, char *ratio, char **rgb)
{
	t_dotrt	*rt;

	rt = single_rt();
	rt->l->type = LIGHT;
	rt->l->point = set_tuple(light_point);
	rt->l->ratio = ft_stod(ratio);
	rt->l->color = set_rgb(rgb);
}

int	as_light(char **array)
{
	char		**light_point;
	char		**rgb;
	static int	obj_n = 0;

	light_point = NULL;
	rgb = NULL;
	if (++obj_n > 1)
		return (error_invalid_element(LIGHT, obj_n));
	if (array_len(array) != 4)
		return (error_invalid_element(LIGHT, obj_n));
	if (verify_light_element(array, &light_point, &rgb, obj_n) != VALID)
		return (INVALID);
	set_rt_light(light_point, array[L_RATIO], rgb);
	return (VALID);
}
