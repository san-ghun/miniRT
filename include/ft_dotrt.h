/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dotrt.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:43:00 by sanghupa          #+#    #+#             */
/*   Updated: 2024/05/17 16:49:48 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DOTRT_H
# define FT_DOTRT_H

/*
** =============================================================================
** Dependency
** =============================================================================
*/

# include "vector.h"
# include "hittable.h"

# include "args.h"
# include "macro.h"
# include "get_next_line.h"
# include "from_ms.h"

/// open
# include <fcntl.h>
/// nan
# include <math.h>

/*
** =============================================================================
** Macros
** =============================================================================
*/

# define MAX_SUBRT	100
# define SPACE		' '

/*
** =============================================================================
** Type Definition
** =============================================================================
*/

typedef int		t_bool;

/// @brief This function pointer is used to classify as_object.
typedef int		(*f_type)(char **);

/// @brief This function pointer is used to
/// determine the range of each object's components.
typedef t_bool	(*f_range)(double);

typedef struct s_subrt {
	int			type;
	int			mat_type;
	double		mat_value;
	double		value1;
	double		value2;
	double		ratio;
	t_vec3		point;
	t_vec3		color;
	t_vec3		vector;
	t_vec3		vector2;
}				t_subrt;

typedef struct s_dotrt {
	t_subrt		*a;
	t_subrt		*c;
	t_subrt		*l;
	t_subrt		*sp[MAX_SUBRT];
	t_subrt		*pl[MAX_SUBRT];
	t_subrt		*cy[MAX_SUBRT];
	int			cnt_sp;
	int			cnt_pl;
	int			cnt_cy;
}				t_dotrt;

/*
** =============================================================================
** Type Definition enumerations for indexing
** =============================================================================
*/

/// give each element the index it requires to make sure it's safe to use
/// even if it's modified in the future
/// @enum ambient light
typedef	enum e_a {
	A_RATIO = 1,
	A_RGB
}	t_a;

/// @enum camera
typedef	enum e_c {
	C_VIEWPOINT = 1,
	C_VECTOR,
	C_FOV
}	t_c;

/// @enum light
typedef enum e_l {
	L_POINT = 1,
	L_RATIO,
	L_RGB
}	t_l;

/// @enum sphere
typedef enum e_sp {
	SP_POINT = 1,
	SP_DIAMETER,
	SP_RGB
}	t_sp;

/// @enum plane
typedef enum e_pl {
	PL_POINT = 1,
	PL_VECTOR,
	PL_RGB
}	t_pl;

/// @enum cylinder
typedef enum e_cy {
	CY_POINT = 1,
	CY_VECTOR,
	CY_DIAMETER,
	CY_HEIGHT,
	CY_RGB
}	t_cy;


/*
** =============================================================================
** Function
** =============================================================================
*/

/// ft_readrt.c
t_subrt		*init_subrt(void);
t_dotrt		*single_rt(void);
t_dotrt		*read_rt(char *filename);

/// is_format.c
t_bool	is_rgb(double color);
t_bool	is_ratio(double num);
t_bool	is_vector(double vector);
t_bool	is_hov(double hov);
t_bool	is_unit(double unit);

/// as_ambient, camera, light, sphere, plane, and cylinder.c
int		as_ambient(char **array);
int		as_camera(char **array);
int		as_light(char **array);
int		as_sphere(char **array);
int		as_plane(char **array);
int		as_cylinder(char **array);

/// set_tuple.c
int		valid_tuple(char **ele, int id, int i, f_range is_range);
t_vec3	set_tuple(char **v);
t_vec3	set_rgb(char **rgb);

/// utils.c
int		array_len(char **array);
void	ft_arr_free(char **array);
void	unify_spacekind(char *s);

/// debug
void	print_vec3(t_vec3 v);
void	print_object_arr(
		t_subrt **objects, int count, const char *object_type);
void	print_rt(void);

#endif
