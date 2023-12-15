/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:18:53 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/12 01:13:19 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

/*
** =============================================================================
** Dependency
** =============================================================================
*/

# include <stdlib.h>
# include <math.h>
# include <stdint.h>
# include <pthread.h>

/*
** =============================================================================
** Type Definition
** =============================================================================
*/

typedef int		t_bool;

typedef struct s_vec3
{
	double		x;
	double		y;
	double		z;
}				t_vec3;

/*
** =============================================================================
** Function
** =============================================================================
*/

t_vec3	init_vector(double x, double y, double z);

/// @brief addition of two vectors
/// @param u vector
/// @param v vector
/// @return a vector
t_vec3	add(t_vec3 u, t_vec3 v);

/// @brief subtraction of two vectors
/// @param u vector
/// @param v vector
/// @return a vector
t_vec3	subtract(t_vec3 u, t_vec3 v);

/// @brief scale (scalar multiplication) of a vector
/// @param v vector
/// @param s scalar
/// @return a vector
t_vec3	scale(t_vec3 v, double s);

/// @brief dot (inner) product of two vectors
/// @param u vector
/// @param v vector
/// @return (double) a scalar
double	dot(t_vec3 u, t_vec3 v);

/// @brief cross product of two vectors
/// @param u vector
/// @param v vector
/// @return a vector
t_vec3	cross(t_vec3 u, t_vec3 v);

t_vec3	flip(t_vec3 v);
double	len_pow(t_vec3 v);
double	len_sqrt(t_vec3 v);
t_vec3	unit(t_vec3 v);
t_bool	near_zero(t_vec3 v);

#endif
