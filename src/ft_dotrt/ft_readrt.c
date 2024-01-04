/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readrt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:51:48 by sanghupa          #+#    #+#             */
/*   Updated: 2024/01/04 22:49:29 by minakim          ###   ########.fr       */
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

void	ft_free_array(char **array)
{
	while (*array)
		free(*array);
	free(array);
}

int	as_ambient(char **array)
{
	char	**rgb;
	
	if (array_len(array) != 3)
		return (error_invalid_input(FORMAT, AMBIENT, UNDEFINED));
	rgb = ft_split(array[2], ',');
	if (!rgb)
		return (INVALID);
	if (array_len(rgb) != 3)
		return (ft_free_array(rgb), INVALID);
	
}

int	as_camera(char **array)
{

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
		return (ft_free_array(split), INVALID);
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
