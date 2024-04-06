/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:57:57 by minakim           #+#    #+#             */
/*   Updated: 2024/03/13 17:17:45 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	ADDEND_H
#define ADDEND_H

/// basic typedef
typedef int		t_bool;

/// source
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

/// struct
/// @name t_cam_added
typedef struct s_cam_ae
{
	int		keycode;
	t_vec3	addend;
	char	name[20];
}			t_c_addend;

/// @name t_aes objects
typedef struct s_addend
{
	int		keycode;
	int 	type;
	t_vec3	position;
	char	name[30];
}			t_aes;

/// addend/utils.c
t_bool		vecequ(t_vec3 a, t_vec3 b);
t_vec3		nonset(void);

///addend/
void		debug_camera(void);
t_bool		is_camera_position(int keycode);
void		adjust_camera_position(int keycode);

///addend/
void	set_point_with_addend(t_obj *obj, t_aes addend);

///addend/
void		adjust_object(int keycode);
t_bool		is_objects(int keycode);

///addend/
t_bool		is_camera_orientation(int keycode);
void		adjust_camera_orientation(int keycode);

#endif
