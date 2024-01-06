/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 23:02:10 by minakim           #+#    #+#             */
/*   Updated: 2024/01/07 00:27:56 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"

/// @param indentifier
/// Define each element present in the ".rt" file as an `indentifier` object.
/// This param exists to print out the specific place where the error occurred.
/// For `indentifier`, only `Identifier Macros`, in "macros.h" should be entered.

/// @note In the concatenated function,
/// 0 is defined as VALID, so the 0th index, "NOTUSED", is not used.
char	*print_objname(int identifier)
{
	const char *names[] = {
			"NOTUSED",
			"RESOLUTION",
			"AMBIENT",
			"CAMERA",
			"LIGHT",
			"SPHERE",
			"PLANE",
			"CYLINDER",
			"RECTANGLE"
	};
	if (identifier > 0 && identifier < (int)(sizeof (names) / sizeof(names[0])))
	{
		return ((char *)names[identifier]);
	}
	return ("undefine");
}

void	print_correct_formatting(void)
{
	ft_printf("an invalid formatting form was found.\n");
	ft_printf("all forms should be separated by spaces only.\n");
}

void	print_error_location(int indentifier, int index)
{
	ft_printf("Error location: %s\n", print_objname(indentifier));
	ft_printf("corresponding object number: %d\n", index);
	if (index > 1 && is_objunique(indentifier))
		ft_printf("!warning: only one of these objects can exist.\n");
}