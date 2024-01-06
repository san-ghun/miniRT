/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 22:49:49 by minakim           #+#    #+#             */
/*   Updated: 2024/01/07 00:28:09 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"

int	error_wrong_range(int indentifier, int index)
{
	print_error_location(indentifier, index);
	if (indentifier > 0)
		return (indentifier);
	return (42);
}

int	error_invalid_element(int indentifier, int index)
{
	print_error_location(indentifier, index);
	if (indentifier > 0)
		return (indentifier);
	return (42);
}

int error_no_input(void)
{
	ft_printf("please include the .rt file.\n"
			  "./miniRT filename.rt\n");
	return (INVALID);
}