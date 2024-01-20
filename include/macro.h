/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:24:26 by minakim           #+#    #+#             */
/*   Updated: 2024/01/07 16:51:54 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MACRO_H
#define MACRO_H

/*
** -----------------------------------------------------------------------------
** Result Macros
** -----------------------------------------------------------------------------
*/

# define TRUE 			1
# define FALSE 			0
# define VALID			0
# define INVALID		1
# define CHECK			1
# define PARSE			0
# define SUCCESS		1
# define END			0
# define ERROR 			-1

/*
** =============================================================================
** Identifier Macros
** =============================================================================
*/

# define UNDEFINED		-1
# define NOTHING		0
# define RESOLUTION		1
# define AMBIENT		2
# define CAMERA			3
# define LIGHT			4
# define SPHERE			5
# define PLANE			6
# define CYLINDER		7
# define RECTANGLE		8
// # define TRIANGLE		9
// # define CONE			10

/*
** =============================================================================
** Dotrt file
** =============================================================================
*/
# define EXTENSION	".rt"

#endif
