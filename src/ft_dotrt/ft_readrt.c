/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readrt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:51:48 by sanghupa          #+#    #+#             */
/*   Updated: 2024/01/07 17:44:20 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dotrt.h"

f_type	classify_element_type(char *input)
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

int	execute_subrt(char **array)
{
	f_type	func_to_run;

	func_to_run = classify_element_type(array[0]);
	if (func_to_run == NULL)
	{
		ft_printf("error: invalid identifier\n");
		return (INVALID);
	}
	if (func_to_run(array) != VALID)
		return (INVALID);
	return (VALID);
}

int	process_subrt(char *line)
{
	char	**array;

	unify_spacekind(line);
	array = ft_split(line, SPACE);
	if (!array)
		return (INVALID);
	if (execute_subrt(array) != VALID)
			return (ft_arr_free(array), INVALID);
	ft_arr_free(array);
	return (VALID);
}

int	convert_dotrt_format(int fd)
{
	char 	*line;

	line = get_next_line(fd);
	if (!line)
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
		if (process_subrt(line) != VALID)
			return (free(line), INVALID);
		free(line);
		line = get_next_line(fd);
	}
	print_rt(); /// FIXME: del later
	return (VALID);
}

t_dotrt	*read_rt(char *filename)
{
	t_dotrt	*rt;
	int 	fd;

	rt = single_rt();
	if (access(filename, R_OK) != 0)
	{
		ft_printf("error: checking file access.\n");
		return (NULL);
	}
	fd = open(filename, O_RDONLY);
	if (fd <= 0)
	{
		ft_printf("error: can't open file.\n");
		return (NULL);
	}
	if (convert_dotrt_format(fd) != VALID)
	{
		ft_printf("error: target .rt file valid fail.\n");
		close(fd);
		return (NULL);
	}
	close(fd);
	return (rt);
}
