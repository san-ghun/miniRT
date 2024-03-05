/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:28:53 by minakim           #+#    #+#             */
/*   Updated: 2024/03/05 17:29:19 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "args.h"

int	mode_fail(int *target)
{
	*target = MODE_FAIL;
	return (FALSE);
}

int mode_success(char **argv, t_mode *mode, const char *flag)
{
	if (ft_strequ(flag, FLAG_DEBUG))
		mode->debug_mode = TRUE;
	else if (ft_strequ(flag, FLAG_WIDTH))
	{
		mode->image_mode = TRUE;
		mode->image_width = \
		set_image_width(ft_atoi(argv[mode->image_index + 1]));
	}
	else
		return (FALSE);
	return (TRUE);
}

t_bool	try_debug_mode(int argc, char *argv[], t_mode *mode)
{
	int	i;
	
	i = 0;
	if (argc < 3 || argc > 5)
		return (FALSE);
	while (argv[++i] && i < argc)
	{
		if (ft_strequ(argv[i], FLAG_DEBUG))
		{
			if (mode->debug_index == -1)
				mode->debug_index = i;
			else
				return (mode_fail(&(mode->debug_mode)));
		}
	}
	if (mode->debug_index != -1)
		return (mode_success(argv, mode, FLAG_DEBUG));
	return (FALSE);
}

t_bool	try_image_mode(int argc, char *argv[], t_mode *mode)
{
	int	i;
	
	i = 0;
	if (argc < 3 || argc > 5)
		return (FALSE);
	while (argv[++i] && i < argc - 1)
	{
		if (ft_strequ(argv[i], FLAG_WIDTH))
		{
			if (ft_atoi(argv[i + 1]) <= 0 || ft_atoi(argv[i + 1]) > MAX_WIDTH)
				return (printf("width: 1 >= && <= 1921\n"), mode_fail(&(mode->image_mode)));
			if (mode->image_index == -1)
				mode->image_index = i;
			else
				return (mode_fail(&(mode->image_mode)));
		}
	}
	if (mode->image_index != -1)
		return (mode_success(argv, mode, FLAG_WIDTH));
	return (FALSE);
}