/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readrt.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:43:00 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/21 17:08:51 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_READRT_H
# define FT_READRT_H

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
}				t_subrt;

typedef struct s_dotrt {
	t_subrt		a;
	t_subrt		c;
	t_subrt		l;
	t_subrt		*sp;
	t_subrt		*pl;
	t_subrt		*cy;
	int			cnt_sp;
	int			cnt_pl;
	int			cnt_cy;
}				t_dotrt;

/*
** =============================================================================
** Function
** =============================================================================
*/

t_subrt		init_subrt(void);
t_dotrt		*single_rt(void);
t_dotrt		*new_rt(void);

#endif
