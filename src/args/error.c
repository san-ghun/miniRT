/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 22:49:49 by minakim           #+#    #+#             */
/*   Updated: 2024/05/07 17:06:02 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "args.h"

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

int	error_args(int err_code)
{
	printf("args: ");
	if (err_code == ERR_RT_FILE)
		printf("please include one '.rt' file.\n");
	else if (err_code == ERR_ARGS)
		printf("too many/less arguments.\n");
	else if (err_code == ERR_FLAG_FAIL)
		printf("incorrect flag found.\n");
	else if (err_code == ERR_SYNTAX)
		printf("wrong syntax.\n");
	printf("syntax: ./miniRT filename.rt [OPTIONS] ...\n");
	printf("Options:\n");
	printf("  -d,\t\t--debug\tEnable debug mode\n");
	printf("  -w NUMBERIC,\t--width\tChange image width to the specified value\n");
	return (FALSE);
}

/// @param indentifier
/// Define each element present in the ".rt" file as an `indentifier` object.
/// This param exists to print out the specific place where the args occurred.
/// For `indentifier`,
/// only `Identifier Macros`, in "macros.h" should be entered.
t_bool	is_objunique(int indentifier)
{
	if (indentifier == AMBIENT || indentifier == CAMERA || indentifier == LIGHT)
		return (TRUE);
	return (FALSE);
}