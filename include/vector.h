/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:18:53 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/16 17:18:26 by sanghupa         ###   ########.fr       */
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
t_vec3	vadd(t_vec3 u, t_vec3 v);

/// @brief subtraction of two vectors
/// @param u vector
/// @param v vector
/// @return a vector
t_vec3	vsubtract(t_vec3 u, t_vec3 v);

/// @brief scale (scalar multiplication) of a vector
/// @param v vector
/// @param s scalar
/// @return a vector
t_vec3	vscale(t_vec3 v, double s);

/// @brief dot (inner) product of two vectors
/// @param u vector
/// @param v vector
/// @return (double) a scalar
double	vdot(t_vec3 u, t_vec3 v);

/// @brief cross product of two vectors
/// @param u vector
/// @param v vector
/// @return a vector
t_vec3	vcross(t_vec3 u, t_vec3 v);

t_vec3	vflip(t_vec3 v);
double	vlen_pow(t_vec3 v);
double	vlen_sqrt(t_vec3 v);
t_vec3	vunit(t_vec3 v);
t_bool	vnear_zero(t_vec3 v);

t_vec3	vmult(t_vec3 vec, t_vec3 vec2);
t_vec3	vreflect(t_vec3 v, t_vec3 n);
t_vec3	vrefract(t_vec3 uv, t_vec3 n, double etai_over_etat);

t_vec3	vrandom(double min, double max);
t_vec3	vrandom_in_unit_sphere(void);
t_vec3	vrandom_unit_vector(void);
t_vec3	vrandom_on_hemisphere(t_vec3 normal);

#endif
