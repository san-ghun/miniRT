/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:23:13 by minakim           #+#    #+#             */
/*   Updated: 2024/03/05 17:37:26 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "args.h"

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

char	*try_find_rt_file(int argc, char *argv[], t_mode *mode)
{
	int count;
	int indexs[6] = {1, 0, 0, 0, 0, 0};
	int i;
	
	count = argc - 1;
	if (mode->image_mode == TRUE)
	{
		count -= 2;
		indexs[mode->image_index] = 1;
		indexs[mode->image_index + 1] = 1;
	}
	if (mode->debug_mode == TRUE)
	{
		count -= 1;
		indexs[mode->debug_index] = 1;
	}
	if (count == 1)
	{
		i = 1;
		while (indexs[i] && indexs[i] != 0)
			i++;
		mode->rt_index = i;
		return (argv[i]);
	}
	return (NULL);
}

void	find_target(int argc, char *argv[], char *target, int indexs[])
{
	int i;
	
	i = 0;
	while (++i < argc && argv[i])
	{
		if (ft_strequ(target, argv[i]))
		{
			indexs[i] = 1;
			return ;
		}
	}
}

t_bool	check_syntax(int argc, char *argv[])
{
	int indexs[6] = {1, 0, 0, 0, 0, 0};
	int i;
	
	find_target(argc, argv, FLAG_DEBUG, indexs);
	find_target(argc, argv, FLAG_WIDTH, indexs);
	i = 0;
	while (++i < argc && indexs[i])
	{
		if (indexs[i] == 0)
			if (check_filename(argv[i]))
			{
				indexs[i] = 1;
				break ;
			}
	}
	i = 0;
	while (++i < argc && indexs[i])
	{
		if (indexs[i] == 0)
			return (FALSE);
	}
	return (TRUE);
}

t_bool	args_check(int argc, char *argv[])
{
	t_mode	*mode;
	if (argc < 2 || argc > 5)
		return (error_args(ERR_ARGS));
	mode = single_mode();
	if (!check_syntax(argc, argv))
		return (error_args(ERR_SYNTAX));
	else if ((!try_debug_mode(argc, argv, mode) && mode->debug_mode == MODE_FAIL) || \
			(!try_image_mode(argc, argv, mode) && mode->image_mode == MODE_FAIL))
		return (error_args(ERR_FLAG_FAIL));
	else if (!check_filename(try_find_rt_file(argc, argv, mode)))
		return (error_args(ERR_RT_FILE));
	if (mode->image_mode)
		printf("** you are in image mode\n"
			   "ratio: 16 / 9, image width: %d, image hight: %d\n",
			   mode->image_width, (int)(mode->image_width/ mode->ratio));
	if (mode->debug_mode)
		printf("** you are in debug mode\n");
	return (TRUE);
}