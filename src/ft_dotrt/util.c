/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 16:07:14 by minakim           #+#    #+#             */
/*   Updated: 2024/03/13 17:01:45 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dotrt.h"

int array_len(char **array)
{
	int	i;
	
	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	ft_arr_free(char **array)
{
	int	i;
	
	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
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
