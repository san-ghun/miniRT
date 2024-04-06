/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:21:38 by minakim           #+#    #+#             */
/*   Updated: 2024/03/13 18:48:56 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGS_H
#define ARGS_H

#include "libft.h"
#include "from_ms.h"
#include "stdio.h"
#include "macro.h"

typedef int t_bool;

///	@macro
#define	ERR_RT_FILE		42
#define ERR_FLAG_FAIL	43
#define ERR_ARGS		44
#define ERR_SYNTAX		45
#define MAX_WIDTH		1920

/// @flag
#define FLAG_DEBUG		"-d"
#define FLAG_WIDTH		"-w"
#define	MODE_FAIL		-1

# define PROMPT_DEBUG	"miniRT[debug] $"
# define PROMPT_DEFAULT	"miniRT $"

typedef struct s_mode {
	t_bool	debug_mode;
	int 	debug_index;
	t_bool	image_mode;
	int 	image_index;
	int 	image_width;
	double	ratio;
	int		rt_index;
	char	prompt[15];
}		t_mode;

/// @param indentifier Define each element present in the ".rt" file as an `indentifier` object.
/// This param exists to print out the specific place where the error occurred.
/// For `indentifier`, only `Identifier Macros`, in "macros.h" should be entered.

/// print_error.c
void	print_prompt(char *msg);
void	print_prompt_addend(char *target, char *msg);
void	print_prompt_object(char *msg);
char	*print_objname(int identifier);
void	print_correct_formatting(void);


void	print_error_location(int indentifier, int index);

/// bool.c
t_bool	is_objunique(int indentifier);
/// args.c
int		error_wrong_range(int identifier, int index);
int		error_invalid_element(int identifier, int index);
int		error_args(int err_code);
///	single_mode.c
t_mode	*single_mode(void);
int		set_image_width(int width);
void	init_array_6(int arr[]);
t_bool	check_filename(char *filename);

///	args_check.c
t_bool	args_check(int argc, char *argv[]);

/// check_mode.c
t_bool	try_debug_mode(int argc, char *argv[], t_mode *mode);
t_bool	try_image_mode(int argc, char *argv[], t_mode *mode);

#endif
