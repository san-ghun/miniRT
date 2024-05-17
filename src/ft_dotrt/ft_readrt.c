/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readrt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:51:48 by sanghupa          #+#    #+#             */
/*   Updated: 2024/05/17 17:04:25 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dotrt.h"

/// as_sphere, as_plaib, as_cylinder
t_type	classify_element_type(char *input)
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
	t_type		func_to_run;
	static int	msg_trigger = TRUE;

	func_to_run = classify_element_type(array[0]);
	if (func_to_run == NULL)
	{
		if (msg_trigger == TRUE)
		{
			print_prompt("args: invalid identifier.");
			msg_trigger = FALSE;
		}
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
	array = ft_split(line, C_SPACE);
	if (!array)
		return (INVALID);
	if (execute_subrt(array) != VALID)
		return (ft_arr_free(array), INVALID);
	ft_arr_free(array);
	return (VALID);
}

int	convert_dotrt_format(int fd)
{
	char	*line;
	char	*trim;
	int		validate_rt;

	validate_rt = VALID;
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
		trim = ft_strtrim(line, "\n");
		free(line);
		if (process_subrt(trim) != VALID)
			validate_rt = INVALID;
		free(trim);
		line = get_next_line(fd);
	}
	return (print_rt(), validate_rt);
}

t_dotrt	*read_rt(char *filename)
{
	t_dotrt	*rt;
	int		fd;

	rt = single_rt();
	if (access(filename, R_OK) != 0)
	{
		print_prompt("args: checking file access.");
		return (NULL);
	}
	fd = open(filename, O_RDONLY);
	if (fd <= 0)
	{
		print_prompt("args: can't open file.");
		return (NULL);
	}
	if (convert_dotrt_format(fd) != VALID)
	{
		print_prompt("args: target '.rt' file valid fail.");
		return (close(fd), NULL);
	}
	return (close(fd), rt);
}
