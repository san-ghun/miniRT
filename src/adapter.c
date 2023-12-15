/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adapter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 21:47:56 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/14 22:07:33 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	append_obj(t_obj *target)
{
	int			i;
	t_resource	*rsc;

	i = 0;
	rsc = single_rsc();
	while (rsc->objs[i] != NULL)
		i++;
	rsc->objs[i] = target;
	target->id = i;
	target->nth = i;
	rsc->len_objs++;
}
