/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dotrt.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:43:00 by sanghupa          #+#    #+#             */
/*   Updated: 2024/01/03 22:40:26 by minakim          ###   ########.fr       */
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

# include "macro.h"
# include "get_next_line.h"
# include "from_ms.h"
/// open
# include <fcntl.h>

/*
** =============================================================================
** Macros
** =============================================================================
*/

# define MAX_SUBRT 100

/*
** =============================================================================
** Type Definition
** =============================================================================
*/

typedef int		t_bool;

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
** Function
** =============================================================================
*/

/// ft_readrt.c
t_subrt		*init_subrt(void);
t_dotrt		*single_rt(void);
t_dotrt		*new_rt(char *filename);

/// ft_writert.c
void		set_dotrt(t_dotrt *rt);

#endif
