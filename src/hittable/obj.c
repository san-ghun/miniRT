/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 21:35:29 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/15 20:05:54 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"

t_obj	*init_obj(void *data, int type)
{
	t_obj	*this;

	this = malloc(sizeof(t_obj) * 1);
	this->data = data;
	this->type = type;
	this->id = -1;
	this->nth = -1;
	return (this);
}
