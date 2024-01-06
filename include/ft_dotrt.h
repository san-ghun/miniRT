/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dotrt.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:43:00 by sanghupa          #+#    #+#             */
/*   Updated: 2024/01/06 22:43:26 by minakim          ###   ########.fr       */
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

# include "ft_error.h"
# include "macro.h"
# include "get_next_line.h"
# include "from_ms.h"

/// open
# include <fcntl.h>
///
# include <math.h>

/*
** =============================================================================
** Macros
** =============================================================================
*/

# define MAX_SUBRT 100
# define SPACE ' '

/*
** =============================================================================
** Type Definition
** =============================================================================
*/

typedef int		t_bool;
typedef int		(*f_ptr)(char **);
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
** Type Definition Index
** =============================================================================
*/

typedef	enum e_a {
	A_RATIO = 1,
	A_RGB
} t_a;

typedef	enum e_c {
	C_VIEWPOINT = 1,
	C_VECTOR,
	C_FOV
} t_c;


/*
** =============================================================================
** Function
** =============================================================================
*/

/// ft_readrt.c
t_subrt		*init_subrt(void);
t_dotrt		*single_rt(void);
t_dotrt		*new_rt(char *filename);

/// ft_writert.c
void		set_dotrt(t_dotrt *rt);


/// is_format.c
t_bool	is_rgb(double color);
t_bool	is_ratio(double num);
t_bool	is_vector(double vector);
t_bool	is_hov(double hov);
#endif
