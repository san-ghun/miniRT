/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 22:49:49 by minakim           #+#    #+#             */
/*   Updated: 2024/01/04 23:02:07 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"

t_err	error_wrong_range(t_err type, int indentifier, int index)
{
	print_error_location(indentifier, index);
	if (type == FORMAT)
		print_correct_formatting();
	else if (type == COLOR)
		ft_putendl_fd("The range of colors does not fit.", 1);
	else if (type == RATIO)
		ft_putendl_fd("The range of ratio does not fit.", 1);
	else if (type == VECTOR)
		ft_putendl_fd("The range of vector does not fit.", 1);
	return (type);
}

t_err	error_invalid_input(t_err type, int indentifier, int index)
{
	print_error_location(indentifier, index);
	if (type == FORMAT)
		print_correct_formatting();
	else if (type == COLOR)
		ft_putendl_fd("incorrect format found during RGB color conversion", 1);
	else if (type == RATIO)
		ft_putendl_fd("invalid format found while entering ratio", 1);
	else if (type == VECTOR)
		ft_putendl_fd("incorrect format found during vector conversion", 1);
	return (type);
}
