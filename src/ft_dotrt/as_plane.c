/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_plane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 16:18:37 by minakim           #+#    #+#             */
/*   Updated: 2024/01/07 16:40:39 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dotrt.h"

int verify_plane_element(char **array, char ***point, char ***vector, char ***rgb)
{
	t_dotrt	*rt;
	
	rt = single_rt();
	*point = ft_split(array[PL_POINT], ',');
	if (valid_tuple(*point, PLANE, rt->cnt_pl, NULL) != VALID)
		return (INVALID);
	*vector = ft_split(array[PL_VECTOR], ',');
	if (valid_tuple(*vector, PLANE, rt->cnt_pl, is_vector) != VALID)
		return (ft_arr_free(*point), INVALID);
	*rgb = ft_split(array[PL_RGB], ',');
	if (valid_tuple(*rgb, PLANE, rt->cnt_pl, is_rgb) != VALID)
	{
		ft_arr_free(*point);
		ft_arr_free(*vector);
		return (INVALID);
	}
	return (VALID);
}

void	set_rt_plane(char **point, char **vector, char **rgb)
{
	t_dotrt	*rt;
	t_subrt *sub;
	
	rt = single_rt();
	sub = init_subrt();
	sub->type = PLANE;
	sub->point = set_tuple(point);
	sub->vector = set_tuple(vector);
	sub->color = set_rgb(rgb);
	rt->pl[rt->cnt_pl] = sub;
	rt->cnt_pl++;
}

int	as_plane(char **array)
{
	t_dotrt	*rt;
	char	**point;
	char	**vector;
	char	**rgb;
	
	rt = single_rt();
	if (array_len(array) != 4)
		return (error_invalid_element(PLANE, rt->cnt_pl));
	if (verify_plane_element(array, &point, &vector, &rgb) != VALID)
		return (INVALID);
	set_rt_plane(point, vector, rgb);
	return (VALID);
}
