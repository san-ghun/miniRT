/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:29:43 by minakim           #+#    #+#             */
/*   Updated: 2023/12/02 14:12:03 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "from_ms.h"

void	*ft_memalloc(size_t size)
{
	void	*temp;

	temp = (void *)malloc(size);
	if (!temp)
		return (NULL);
	ft_bzero(temp, size);
	return (temp);
}
