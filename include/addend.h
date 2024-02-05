/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:57:57 by minakim           #+#    #+#             */
/*   Updated: 2024/02/05 21:29:32 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	ADDEND_H
#define ADDEND_H

typedef int		t_bool;

# include "vector.h"
# include "macro.h"
# include "camera.h"
# include "ft_dotrt.h"
# include "hittable.h"

/// key mapping
# if __linux__
# include "key_linux.h"
# elif __APPLE__
# include "key_macos.h"
# else
# error "Unknown OS"
# endif

/// printf
# include <stdio.h>

typedef struct s_cam_ae
{
	int		keycode;
	t_vec3	addend;
	char	name[20];
}			t_c_addend;

typedef struct s_addend
{
	int		keycode;
	int 	type;
	t_vec3	position;
	char	name[20];
}			t_addends;

// addend/utils.c
t_bool		vecequ(t_vec3 a, t_vec3 b);
t_vec3		non_set(void);

void		debug_camera(void);
t_bool		is_camera_position(int keycode);

t_plane		*pl_add_position(t_plane *pl, t_addends addend);
t_sphere	*sp_add_position(t_sphere *sp, t_addends addend);
t_cylinder	*cy_add_position(t_cylinder *cy, t_addends addend);

void		adjust_object(int keycode);
t_bool		is_objects(int keycode);

t_bool		is_camera_orientation(int keycode);
void		adjust_camera_orientation(int keycode);
#endif
