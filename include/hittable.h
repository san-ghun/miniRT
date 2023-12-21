/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:47:39 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/21 16:45:43 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITTABLE_H
# define HITTABLE_H

/*
** =============================================================================
** Dependency
** =============================================================================
*/

# include "libft.h"
# include "ray.h"
# include "interval.h"
# include "vector.h"
# include "ft_random.h"

/*
** =============================================================================
** Identifier Macros
** =============================================================================
*/

# define NOTHING		0
# define RESOLUTION		1
# define AMBIENT		2
# define CAMERA			3
# define LIGHT			4
# define SPHERE			5
# define PLANE			6
# define CYLINDER		7
// # define SQUARE			8
// # define TRIANGLE		9
// # define CONE			10

/*
** =============================================================================
** Type Definition
** =============================================================================
*/

typedef int		t_bool;

typedef struct s_material
{
	int			type;	// 0:lambertian | 1:metal | 2:dielectric | ...
	t_vec3		albedo;
	double		fuzz;
	double		index_of_refraction;
}				t_material;

typedef struct s_sphere
{
	t_vec3		center;
	double		radius;
	t_material	*mat;
}				t_sphere;

typedef struct s_obj
{
	int			id;
	int			type;
	int			nth;
	void		*data;
	t_material	*material;
}				t_obj;

typedef struct s_hit
{
	t_vec3		point;
	t_vec3		normal;
	double		t;
	t_material	*mat;
	t_bool		front_face;
}				t_hit;

/*
** =============================================================================
** Function
** =============================================================================
*/

/// obj.c
t_obj		*init_obj(void *data, int type, t_material *material);

/// hit_record.c
t_hit		init_rec(void);
void		set_face_normal(t_hit *rec, t_ray ray, t_vec3 outward_normal);
t_bool		hit_objs(t_obj *objs[], t_ray ray, t_interval interval, t_hit *rec);

/// sphere.c
t_sphere	*init_sphere(t_vec3 center, double radius, t_material *material);
t_bool		hit_sphere(void *data, t_ray ray, t_interval interval, t_hit *rec);

/// material.c
t_material	*init_material(int type, t_vec3 color, double fuzz, double ir);
t_bool		scatter(t_ray *r, t_hit *rec, t_vec3 *color);

#endif
