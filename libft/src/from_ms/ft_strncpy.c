/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 13:32:42 by minakim           #+#    #+#             */
/*   Updated: 2023/12/02 14:04:30 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "from_ms.h"

char	*ft_strncpy(char *dest, const char *src, size_t size);

char	*ft_strncpy(char *dest, const char *src, size_t size)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < size)
	{
		dest[i] = src[i];
		++i;
	}
	while (i < size)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
