/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:17:47 by minakim           #+#    #+#             */
/*   Updated: 2024/03/13 17:12:58 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "args.h"

int	set_image_width(int width)
{
	int	remainder;

	remainder = width % N_THREAD;
	if (remainder != 0)
		width += (N_THREAD - remainder);
	return (width);
}

t_mode	*single_mode(void)
{
	static t_mode	this;
	static int		is_init;

	if (is_init)
		return (&this);
	this = (t_mode){
		.image_mode = FALSE,
		.image_index = -1,
		.image_width = set_image_width(1000),
		.ratio = 16.0 / 9.0,
		.debug_mode = FALSE,
		.debug_index = -1,
	};
	ft_strlcpy(this.prompt, PROMPT_DEFAULT, ft_strlen(PROMPT_DEFAULT) + 1);
	is_init = TRUE;
	return (&this);
}

void	init_array_6(int arr[])
{
	int	i;

	i = 1;
	arr[0] = 1;
	while (i < 6)
		arr[i++] = 0;
}

t_bool	check_filename(char *filename)
{
	int	len;
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
