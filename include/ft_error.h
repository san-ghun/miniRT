/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 22:51:58 by minakim           #+#    #+#             */
/*   Updated: 2024/01/06 22:26:25 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
#define ERROR_H

#include "libft.h"
#include "ft_printf.h"
#include "macro.h"

typedef int t_bool;

typedef enum e_err{
	FORMAT = 2,
	COLOR,
	RATIO,
	VECTOR,
	VIEWPOINT,
	HOV
} t_err;

/// @param indentifier Define each element present in the ".rt" file as an `indentifier` object.
/// This param exists to print out the specific place where the error occurred.
/// For `indentifier`, only `Identifier Macros`, in "macros.h" should be entered.

/// print_error.c
int		print_objname(int identifier);
void	print_correct_formatting(void);
void	print_error_location(int indentifier, int index);

/// bool.c
t_bool	is_objunique(int indentifier);

/// error.c
int	error_wrong_range(int indentifier, int index);
int	error_invalid_element(int indentifier, int index);

#endif
