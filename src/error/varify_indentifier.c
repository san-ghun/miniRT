/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 22:58:38 by minakim           #+#    #+#             */
/*   Updated: 2024/01/04 23:00:21 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"

t_bool	is_objunique(int indentifier)
{
	if (indentifier == AMBIENT || indentifier == CAMERA || indentifier == LIGHT)
		return (TRUE);
	return (FALSE);
}