/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 21:55:10 by minakim           #+#    #+#             */
/*   Updated: 2024/01/03 22:08:03 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "valid.h"

t_bool	check_filename(char *filename)
{
	int len;
	int	e_len;
	
	if (!filename)
		return (FALSE);
	len = ft_strlen(filename);
	if (len < 4)
		return (FALSE);
	e_len = ft_strlen(EXTENSION);
	if (!ft_strnequ(&filename[len - e_len], EXTENSION, e_len))
		return (FALSE);
	return (TRUE);
}

t_bool	check_input(int argc, char *argv[])
{
	if (argc != 2)
		return (FALSE);
	if (!check_filename(argv[1]))
		return (FALSE);
}

t_bool	check_rgb();
t_bool	check_vector();
