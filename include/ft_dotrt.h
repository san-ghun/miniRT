/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dotrt.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:43:00 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/29 14:43:59 by sanghupa         ###   ########.fr       */
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

/*
** =============================================================================
** Type Definition
** =============================================================================
*/

typedef int		t_bool;

typedef struct s_subrt {
	int			type;
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
	t_subrt		*sp[100];
	t_subrt		*pl[100];
	t_subrt		*re[100];
	t_subrt		*cy[100];
	int			cnt_sp;
	int			cnt_pl;
	int			cnt_re;
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
t_dotrt		*new_rt(void);

/// ft_writert.c
void		set_dotrt(t_dotrt *rt);

#endif
