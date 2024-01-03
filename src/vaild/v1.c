/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v1.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:19:28 by minakim           #+#    #+#             */
/*   Updated: 2024/01/03 17:57:10 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "valid.h"


/// TODO: if need, add error msg
t_bool	check_extension(int argc, char *argv[])
{
	int len;
	int	e_len;

	if (argc != 2)
		return (FALSE);
	len = ft_strlen(argv[1]);
	e_len = ft_strlen(EXTENSION);
	if (!ft_strnequ(&argv[1][len - e_len], EXTENSION, e_len))
		return (FALSE);
	return (TRUE);
}

int	open_dotrt(int argc, char *argv[])
{
	int	fd;

	if (!check_extension(argc, argv))
		return (FALSE);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0 || fd == 0)
		return (FALSE);
	return (fd);
}

/// @note

t_bool	read_rt(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (FALSE); // empty map check
}