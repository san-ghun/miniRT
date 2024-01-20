/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:42:30 by minakim           #+#    #+#             */
/*   Updated: 2024/01/06 20:30:37 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "from_ms.h"
#include <math.h>

#define FALSE	0
#define TRUE	1

void	process_sign(const char **s, int *sign)
{
	while (ft_isspace(**s))
		(*s)++;
	if (**s == '-')
		*sign = -1;
	if (**s == '-' || **s == '+')
		(*s)++;
}

double	parse_digit(char c, double res, int point, double *decimal_place)
{
	if (!point)
		res = res * 10.0 + (c - '0');
	else
	{
		res = res + (c - '0') / (*decimal_place);
		*decimal_place *= 10.0;
	}
	return (res);
}

double	ft_stod(const char *s)
{
	int		sign;
	double	res;
	double	decimal_place;
	int		found_point;

	res = 0;
	sign = 1;
	found_point = FALSE;
	decimal_place = 10.0;
	process_sign(&s, &sign);
	while (*s)
	{
		if (ft_isdigit(*s))
			res = parse_digit(*s, res, found_point, &decimal_place);
		else if (*s == '.')
			found_point = TRUE;
		else
			return (nan(""));
		s++;
	}
	return (res * sign);
}

/*
#include <stdio.h>
int main(int ac, char **av)
{
	if (ac == 2)
	{
		printf("%f\n",  ft_stod(av[1]));
	}
	return (0);
}*/

/*
double	ft_stod(const char *s)
{
	int		sign;
	double	res;
	double	decimal_place;
	int		flag;
	
	res = 0;
	sign = 1;
	flag = FALSE;
	decimal_place = 10.0;
	while(ft_isspace(*s))
		s++;
	if (*s == '-')
		sign = -1;
	if (*s == '-' || *s == '+')
		s++;
	while (*s)
	{
		if (ft_isdigit(*s))
		{
			if (!flag)
				res = res * 10.0 + (*s - '0');
			else
			{
				res = res + (*s - '0') / decimal_place;
				decimal_place *= 10.0;
			}
		}
		else if (*s)
			flag = TRUE;
		else
			return (0.0);
		s++;
	}
	return (res * sign / decimal_place);
}*/
