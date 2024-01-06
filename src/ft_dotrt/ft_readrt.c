/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readrt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:51:48 by sanghupa          #+#    #+#             */
/*   Updated: 2024/01/06 22:58:23 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dotrt.h"

t_subrt	*init_subrt(void)
{
	t_subrt	*this;

	this = malloc(sizeof(t_subrt) * 1);
	this->type = NOTHING;
	this->mat_type = 0;
	this->mat_value = 0.0;
	this->value1 = 0.0;
	this->value2 = 0.0;
	this->ratio = 0.0;
	this->point = init_vector(0.0, 0.0, 0.0);
	this->color = init_vector(0.0, 0.0, 0.0);
	this->vector = init_vector(0.0, 0.0, 0.0);
	this->vector2 = init_vector(0.0, 0.0, 0.0);
	return (this);
}

t_dotrt	*single_rt(void)
{
	static t_dotrt	this;
	static int		is_init;

	if (is_init)
		return (&this);
	this = (t_dotrt){
		.a = init_subrt(),
		.c = init_subrt(),
		.l = init_subrt(),
		.sp = {},
		.pl = {},
		.cy = {},
		.cnt_sp = 0,
		.cnt_pl = 0,
		.cnt_cy = 0,
	};
	ft_bzero(this.sp, MAX_SUBRT);
	ft_bzero(this.pl, MAX_SUBRT);
	ft_bzero(this.cy, MAX_SUBRT);
	is_init = 1;
	return (&this);
}

///

int array_len(char **array)
{
	int	i;
	
	i = 0;
	while(*array)
		i++;
	return (i);
}

void	ft_arr_free(char **array)
{
	while (*array)
		free(*array);
	free(array);
}

int	valid_tuple(char **ele, int id, int i, f_range is_range)
{
	double	val;
	
	if (!ele)
		return (INVALID);
	if (array_len(ele) != 3)
	{
		ft_arr_free(ele);
		return (error_invalid_element(id, i));
	}
	while (*ele)
	{
		val = ft_stod(*ele);
		if (isnan(val))
			return (ft_arr_free(ele), error_invalid_element(id, i));
		if (is_range && !is_range(val))
			return (ft_arr_free(ele), error_wrong_range(id, i));
		ele++;
	}
	return (VALID);
}

t_bool	check_ratio_range(char *ratio, int obj_n, int id)
{
	if (!is_ratio(ft_stod(ratio)))
	{
		error_wrong_range(id, obj_n);
		return (FALSE);
	}
	return (TRUE);
}

t_bool	verify_ambient_element(char *ratio, char **array, int obj_n)
{
	char	**rgb;
	if (obj_n > 1)
		return (error_invalid_element(AMBIENT, obj_n));
	if (!check_ratio_range(ratio, obj_n, AMBIENT))
		return (FALSE);
	rgb = ft_split(array[A_RGB], ',');
	if (valid_tuple(rgb, AMBIENT, obj_n, is_rgb) != VALID)
		return (INVALID);
	return (TRUE);
}

double	rgb_conv(char *target)
{
	double	res;
	
	res = 0.0;
	res = ft_stod(target);
	return (res / 255.0);
}

t_vec3	set_rgb(char **rgb)
{
	t_vec3	target;
	
	target = (t_vec3){rgb_conv(rgb[0]), rgb_conv(rgb[1]), rgb_conv(rgb[2])};
	return (target);
}


void	set_rt_ambient(char *ratio, char **rgb)
{
	t_dotrt		*rt;

	rt = single_rt();
	rt->a->type = AMBIENT;
	rt->a->ratio = ft_stod(ratio);
	rt->a->color = set_rgb(rgb);
	ft_arr_free(rgb);
}

int	as_ambient(char **array)
{
	char	**rgb;
	
	static int	obj_n = 0;
	
	if (++obj_n > 1)
		return (error_invalid_element(AMBIENT, obj_n));
	if (array_len(array) != 3)
		return (error_invalid_element(AMBIENT, obj_n));
	if (!verify_ambient_element(array[A_RATIO], rgb, obj_n))
		return (INVALID);
	set_rt_ambient(array[A_RATIO], rgb);
	return (VALID);
}

int	verify_camera_element(char **array, char **view_point, char **vector, int obj_n)
{
	double	fov;
	
	fov = ft_stod(array[C_FOV]);
	if (isnan(fov) || !is_hov(fov))
		return (error_invalid_element(HOV, obj_n));
	view_point = ft_split(array[C_VIEWPOINT], ',');
	if (valid_tuple(view_point, CAMERA, obj_n, NULL) != VALID)
		return (INVALID);
	vector = ft_split(array[C_VECTOR], ',');
	if (valid_tuple(vector, CAMERA, obj_n, is_vector) != VALID)
	{
		ft_arr_free(view_point);
		return (INVALID);
	}
	return (VALID);
}

t_vec3	set_tuple(char **v)
{
	t_vec3	target;
	
	target = (t_vec3){ft_stod(v[0]), ft_stod(v[1]), ft_stod(v[2])};
	return (target);
}


void	set_rt_camera(char **view_point, char **vector)
{
	t_dotrt		*rt;
	
	rt = single_rt();
	rt->c->type = CAMERA;
	rt->c->point = set_tuple(view_point);
	rt->c->vector = set_tuple(vector);
	ft_arr_free(view_point);
	ft_arr_free(vector);
}

int	as_camera(char **array)
{
	char	**view_point;
	char	**vector;
	static int	obj_n = 0;
	
	if (++obj_n > 1)
		return (error_invalid_element(CAMERA, obj_n));
	if (array_len(array) != 4)
		return (error_invalid_element(CAMERA, obj_n));
	if (verify_camera_element(array, view_point, vector, obj_n) != VALID)
		return (INVALID);
	set_rt_camera(view_point, vector);
	return (VALID);
}

int	as_light(char **array)
{

}

int	as_sphere(char **array)
{

}

int	as_plane(char **array)
{

}

int	as_cylinder(char **array)
{

}

f_ptr	classify_subrt(char *input)
{
	if (ft_strnequ(input, "A", 2))
		return (as_ambient);
	else if (ft_strnequ(input, "C", 2))
		return (as_camera);
	else if (ft_strnequ(input, "L", 2))
		return (as_light);
	else if (ft_strnequ(input, "sp", 3))
		return (as_sphere);
	else if (ft_strnequ(input, "pl", 3))
		return (as_plane);
	else if (ft_strnequ(input, "cy", 3))
		return (as_cylinder);
	else
		return (NULL);
}

int	process_input(char **split)
{
	f_ptr	func_to_run;
	
	func_to_run = classify_subrt(split[0]);
	if (func_to_run == NULL)
		return (INVALID); /// error msg?
	if (func_to_run(split) != VALID)
		return (INVALID);
	return (VALID);
}

t_bool	is_whitespace(char c)
{
	if (c == '\t' || c == '\v' || \
		c == '\f' || c == '\r')
		return (TRUE);
	return (FALSE);
}

void	unify_spacekind(char *s)
{
	while (*s)
	{
		if (is_whitespace(*s))
			*s = SPACE;
		s++;
	}
}

int	set_subrt(char *line)
{
	char	**split;
	
	unify_spacekind(line);
	split = ft_split(line, SPACE);
	if (!split)
		return (INVALID);
	if (process_input(split) != VALID)
		return (ft_arr_free(split), INVALID);
	return (VALID);
}

int	convert_dotrt_format(int fd)
{
	char 	*line;
	
	line = get_next_line(fd);
	if (!line) /// empty
		return (INVALID);
	while (line)
	{
		if (line[0] == '\n' || line[0] == '\0')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		line = ft_strtrim(line, "\n");
		if (set_subrt(line) != INVALID)
			return (free(line), INVALID);
		free(line);
		line = get_next_line(fd);
	}
	return (VALID);
}

t_dotrt	*new_rt(char *filename)
{
	t_dotrt	*rt;
	int 	fd;
	
	rt = single_rt();
	fd = open(filename, O_RDONLY);
	if (fd <= 0)
		return (NULL); /// end program
	if (convert_dotrt_format(fd) != VALID)
		return (NULL); /// end program
	return (rt);
}
