/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:23:17 by sanghupa          #+#    #+#             */
/*   Updated: 2024/01/01 12:58:37 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/*
** =============================================================================
** Dependency
** =============================================================================
*/

/// open, close
# include <fcntl.h>

/// read, write
# include <unistd.h>

/// printf, perror
# include <stdio.h>

/// strerror
# include <string.h>

/// malloc, free, exit
# include <stdlib.h>

# include <math.h>
# include <stdint.h>
# include <pthread.h>
# include <limits.h>

/// minilibx
# include "mlx.h"

/// libft
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include "from_ms.h"

/// source
# include "color.h"
# include "vector.h"
# include "ray.h"
# include "hittable.h"
# include "interval.h"
# include "camera.h"
# include "ft_dotrt.h"

/// key mapping
# if __linux__
# include "key_linux.h"
# elif __APPLE__
# include "key_macos.h"
# else
# error "Unknown OS"
# endif

/*
** =============================================================================
** Macro
** =============================================================================
*/ 

/// Limit Loop: use addition to while condition (dev)
# define MAX_ITER	5000

/// Prevent Heap mem leak: use addition to char or array (dev)
# define DATA_SIZE	3072

# define INTMAX		2147483647
# define INTMIN		-2147483648

# define N_THREAD	8

/*
** -----------------------------------------------------------------------------
** Result Macros
** -----------------------------------------------------------------------------
*/

# define TRUE 			1
# define FALSE 			0
# define VALID			0
# define INVALID		1
# define CHECK			1
# define PARSE			0
# define SUCCESS		1
# define END			0
# define ERROR 			-1

/*
** =============================================================================
** Type Definition
** =============================================================================
*/

typedef int				t_bool;
typedef pthread_mutex_t	t_mux;

typedef struct s_square {
	int			x;
	int			y;
	int			size;
	int			color;
}				t_square;

typedef struct s_thread
{
	pthread_t	*pth;
	int			id;
}				t_thread;

typedef struct s_resource {
	t_obj		*objs[100];
	t_material	*mats[100];
	int			len_objs;
	int			len_mats;
	t_thread	**pths;
	t_mux		*lock;
}				t_resource;

typedef struct s_temp {
	int			size;
	int			color;
	int			counter;
}				t_temp;

typedef struct s_container {
	void		*img;
	char		*addr;
	int			h;
	int			w;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_container;

typedef struct s_vars {
	void		*mlx;
	void		*win;
	int			height;
	int			width;
	t_container	*container;
}				t_vars;

/*
** =============================================================================
** Function
** =============================================================================
*/

/// new.c
t_vars		*new_program(int w, int h, char *str);
t_container	*new_container(int w, int h, t_vars *vars);
t_resource	*new_resource(void);

/// singleton.c
t_vars		*single_vars(void);
t_resource	*single_rsc(void);

/// close.c
void		ft_free_2d(void **targets);
int			close_mlx(t_container *img);

/// hook_key.c
int			key_hooks(int keycode, t_container *img);

/// hook_mouse.c
int			mouse_hooks(int button, int m_x, int m_y, t_container *img);

/// mlx_util.c
void		put_pixel_data(t_container *cont, int x, int y, int color);
void		draw_square(t_square square, t_container *img);
t_temp		*single_temp(void);

/// multithread.c
void		render(void);

/// adapter.c
void		append_obj(t_obj *target);
void		append_mat(t_material *target, char *name);
t_material	*find_mat(char *name);
void		apply_dotrt(t_dotrt *rt);

#endif
