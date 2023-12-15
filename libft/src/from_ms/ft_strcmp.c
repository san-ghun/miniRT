/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:00:40 by minakim           #+#    #+#             */
/*   Updated: 2023/12/02 14:04:30 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "from_ms.h"

/// @brief Compares strings `s1` and `s2`, returning the ASCII difference of
/// the first mismatch or 0 if identical.
/// The comparison is based on the length of string s1
int	ft_strcmp(char const *s1, char const *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
