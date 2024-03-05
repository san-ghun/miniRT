/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 23:02:10 by minakim           #+#    #+#             */
/*   Updated: 2024/03/05 17:32:29 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "args.h"

/// @param indentifier
/// Define each element present in the ".rt" file as an `indentifier` object.
/// This param exists to print out the specific place where the args occurred.
/// For `indentifier`, only `Identifier Macros`, in "macros.h" should be entered.
t_bool	is_objunique(int indentifier)
{
	if (indentifier == AMBIENT || indentifier == CAMERA || indentifier == LIGHT)
		return (TRUE);
	return (FALSE);
}

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
		return ((char *)names[identifier]);
	return ("undefine");
}

void	print_correct_formatting(void)
{
	printf("an invalid formatting form was found.\n");
	printf("all forms should be separated by spaces only.\n");
}

void	print_error_location(int indentifier, int index)
{
	printf("Error location: %s\n", print_objname(indentifier));
	printf("corresponding object number: %d\n", index);
	if (index > 1 && is_objunique(indentifier))
		printf("!warning: only one of these objects can exist.\n");
}