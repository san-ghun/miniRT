/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_ambient.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 16:16:29 by minakim           #+#    #+#             */
/*   Updated: 2024/03/05 19:59:09 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// @note The as_object functions all have a similar design.
/// I document this function as a sample.
#include "ft_dotrt.h"

int		verify_ambient_element(char **array, char ***rgb, int obj_n);
void	set_rt_ambient(char *ratio, char **rgb);

/// \param	array This array is the result of ft_split args by SPACE.
///	`free` this array at `process_subrt` function
/// \return	to valid/invalid
///		@line_33: Determine how many elements target object needs
///		@line_35: array is mallocated in this step,
/// 	and each element is validated. If any of them fail,
/// 	it returns "free" followed by invalid.
///		@line_39: after array input to dotrt,
/// 	`free` that array at `set_rgb` or `set_tuple`.
int	as_ambient(char **array)
{
	char		**rgb;
	static int	obj_n = 0;

	rgb = NULL;
	if (++obj_n > 1)
		return (error_invalid_element(AMBIENT, obj_n));
	if (array_len(array) != 3)
		return (error_invalid_element(AMBIENT, obj_n));
	if (verify_ambient_element(array, &rgb, obj_n) != VALID)
		return (INVALID);
	set_rt_ambient(array[A_RATIO], rgb);
	return (VALID);
}

/// \param array used for RGB and ratio conversions.
/// \param rgb is divided by `ft_split` in this function,
/// with delimit set to COMMA and memory allocated.
/// \param obj_n Parameters for the uniqueness check.
/// This check is already done in other functions,
/// but I've added it for extra safety.
/// 	@line_63 if converting a string to a double fails,
/// 	ft_stod returns nan("").
/// 	`isnan` checks the result to validate result of ft_stod.
///		! "nan" dependency on <math.h>
/// \return to valid/invalid
int	verify_ambient_element(char **array, char ***rgb, int obj_n)
{
	double	ratio;

	if (obj_n > 1)
		return (error_invalid_element(AMBIENT, obj_n));
	ratio = ft_stod(array[A_RATIO]);
	if (isnan(ratio) || !is_ratio(ratio))
		return (error_invalid_element(AMBIENT, obj_n));
	*rgb = ft_split(array[A_RGB], ',');
	if (valid_tuple(*rgb, AMBIENT, obj_n, is_rgb) != VALID)
		return (INVALID);
	return (VALID);
}

/// \param rgb set_rgb converts the target to the correct format,
/// and returns its value.
/// Once this is done, the param rgb is free from set_rgb.
void	set_rt_ambient(char *ratio, char **rgb)
{
	t_dotrt		*rt;

	rt = single_rt();
	rt->a->type = AMBIENT;
	rt->a->ratio = ft_stod(ratio);
	rt->a->color = set_rgb(rgb);
}
