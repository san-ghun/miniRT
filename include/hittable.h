/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:47:39 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/29 14:41:13 by sanghupa         ###   ########.fr       */
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
# include "aabb.h"
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
# define RECTANGLE		8
// # define TRIANGLE		9
// # define CONE			10

/*
** =============================================================================
** Type Definition
** =============================================================================
*/

typedef int		t_bool;

typedef struct s_texture
{
	int			type;	// 0:solid | 1:light
	t_vec3		color;
}				t_texture;

typedef struct s_material
{
	int			type;	// 0:lambertian | 1:metal | 2:dielectric | ...
	char		name[64];
	t_vec3		albedo;
	double		fuzz;
	double		index_of_refraction;
	t_vec3		emit_color;
}				t_material;

typedef struct s_sphere
{
	t_vec3		center;
	double		radius;
	t_material	*mat;
	t_texture	*tex;
	t_vec3		translate;
	double		rotate_angle;
}				t_sphere;

typedef struct s_plane
{
	t_vec3		point;
	t_vec3		u;
	t_vec3		v;
	t_aabb		box;
	t_vec3		normal;
	double		d;
	t_vec3		w;
	t_material	*mat;
	t_texture	*tex;
	t_vec3		translate;
	double		rotate_angle;
}				t_plane;

typedef struct s_rectangle
{
	t_vec3		point;
	t_vec3		u;
	t_vec3		v;
	t_aabb		box;
	t_vec3		normal;
	double		d;
	t_vec3		w;
	t_material	*mat;
	t_texture	*tex;
	t_vec3		translate;
	double		rotate_angle;
}				t_rectangle;

typedef struct s_cylinder
{
	t_vec3		center;
	t_vec3		normal;
	double		radius;
	double		height;
	t_vec3		tc;
	t_vec3		bc;
	t_material	*mat;
	t_texture	*tex;
	t_vec3		translate;
	double		rotate_angle;
}				t_cylinder;

typedef struct s_obj
{
	int			id;
	int			type;
	int			nth;
	void		*data;
	t_material	*material;
	t_texture	*texture;
}				t_obj;

typedef struct s_hit
{
	t_vec3		point;
	t_vec3		normal;
	double		t;
	double		u;
	double		v;
	t_material	*mat;
	t_texture	*tex;
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
t_bool		obj_visible(t_ray ray, double lim, t_obj *objs[]);

/// sphere.c
t_sphere	*init_sphere(t_vec3 center, double radius, t_material *material);
t_bool		hit_sphere(void *data, t_ray ray, t_interval interval, t_hit *rec);
t_bool		interfere_sp(void *data, t_ray r, double lim);

/// plane.c
t_plane		*init_plane(t_vec3 point, t_vec3 u, t_vec3 v, t_material *material);
t_bool		hit_plane(void *data, t_ray ray, t_interval interval, t_hit *rec);
t_bool		interfere_pl(void *data, t_ray r, double lim);

/// rectangle.c
t_rectangle	*init_rectangle(t_vec3 point, t_vec3 u, t_vec3 v, t_material *material);
t_bool		hit_rectangle(void *data, t_ray ray, t_interval interval, t_hit *rec);
t_bool		interfere_re(void *data, t_ray r, double lim);

/// cylinder.c
t_cylinder	*init_cylinder(t_vec3 center, double radius, double height, t_material *material);
t_bool		hit_cylinder(void *data, t_ray ray, t_interval interval, t_hit *rec);
t_bool		interfere_cy(void *data, t_ray r, double lim);

/// material.c
t_material	*init_material(int type, t_vec3 color, double fuzz, double ir);
t_bool		scatter(t_ray *r, t_hit *rec, t_vec3 *color);

/// texture.c
t_texture	*init_texture(int type, t_vec3 color);
t_vec3		texture_color(t_texture *tex, double u, double v, t_vec3 point);

#endif
