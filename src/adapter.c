/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adapter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 21:47:56 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/24 18:31:32 by sanghupa         ###   ########.fr       */
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

void	append_mat(t_material *target, char *name)
{
	int			i;
	t_resource	*rsc;

	i = 0;
	rsc = single_rsc();
	ft_strlcpy(target->name, name, ft_strlen(name) + 1);
	while (rsc->mats[i] != NULL)
		i++;
	rsc->mats[i] = target;
	rsc->len_objs++;
}

t_material	*find_mat(char *name)
{
	int			i;
	t_resource	*rsc;

	i = 0;
	rsc = single_rsc();
	while (rsc->mats[i] != NULL)
	{
		if (ft_strncmp(name, rsc->mats[i]->name, ft_strlen(name)) == 0)
			return (rsc->mats[i]);
		i++;
	}
	return (NULL);
}
