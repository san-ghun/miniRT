/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 22:49:49 by minakim           #+#    #+#             */
/*   Updated: 2024/01/07 16:54:29 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"

int	error_wrong_range(int identifier, int index)
{
	print_error_location(identifier, index);
	if (identifier > 0)
		return (identifier);
	return (42);
}

int	error_invalid_element(int identifier, int index)
{
	print_error_location(identifier, index);
	if (identifier > 0)
		return (identifier);
	return (42);
}

int error_no_input(void)
{
	ft_printf("please include the .rt file.\n"
			  "./miniRT filename.rt\n");
	return (INVALID);
}