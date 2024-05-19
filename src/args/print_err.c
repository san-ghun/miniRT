/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 23:02:10 by minakim           #+#    #+#             */
/*   Updated: 2024/05/07 20:37:01 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "args.h"

void	print_prompt(char *msg)
{
	t_mode	*mode;

	mode = single_mode();
	if (msg == NULL)
		printf("%s", mode->prompt);
	else
		printf("%s%s\n", mode->prompt, msg);
}

void	print_prompt_addend(char *target, char *msg)
{
	t_mode	*mode;

	mode = single_mode();
	if (mode->debug_mode == TRUE)
	{
		printf("--------------------------------------------------\n");
		printf("%s%s: %s\n", mode->prompt, target, msg);
		printf("--------------------------------------------------\n");
	}
	else
		printf("%s%s: %s\n", mode->prompt, target, msg);
}

void	print_prompt_object(char *msg)
{
	t_mode	*mode;

	mode = single_mode();
	if (mode->debug_mode == TRUE)
	{
		printf("--------------------------------------------------\n");
		printf("%s    %s\n", mode->prompt, msg);
		printf("--------------------------------------------------\n");
		printf("\n\n");
	}
	else
		printf("%s    %s\n", mode->prompt, msg);
}

/// @note In the concatenated function,
/// 0 is defined as VALID, so the 0th index, "NOTUSED", is not used.
char	*print_objname(int identifier)
{
	const char	*names[] = {
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

void	print_error_location(int indentifier, int index)
{
	print_prompt(NULL);
	printf("Error location: %s\n", print_objname(indentifier));
	printf("corresponding object number: %d\n", index);
	if (index > 1 && is_objunique(indentifier))
		printf("!warning: only one of these objects can exist.\n");
}
