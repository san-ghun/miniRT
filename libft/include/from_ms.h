/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_ms.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:00:17 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/02 14:12:15 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FROM_MS_H
# define FROM_MS_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

char	*ft_strpbrk(const char *str, const char *delim);
size_t	ft_strspn(const char *str, const char *delim);
char	*ft_strtok(char *str, const char *delim);
size_t	ft_strcspn(const char *str, const char *delim);
char	*ft_strncpy(char *dest, const char *src, size_t size);
char	*ft_strndup(const char *src, size_t len);
void	*ft_memalloc(size_t size);
char	*ft_strcdup(const char *src, char c);
int		ft_strequ(char const *s1, char const *s2);
int		ft_strcmp(char const *s1, char const *s2);
int		ft_isspace(char c);
int		ft_strnequ(char const *s1, char const *s2, size_t i);

#endif
