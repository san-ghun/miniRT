/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 13:08:51 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/29 17:08:37 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "interval.h"
#include "ft_printf.h"
#include <math.h>

double	linear_to_gamma(double linear_component)
{
	if (linear_component < 0)
		return (-1 * sqrt(-linear_component));
	return (sqrt(linear_component));
}

t_vec3	get_rgb(double red, double green, double blue)
{
	t_interval	intensity;

	intensity = init_interval(0.000, 0.999);
	red = linear_to_gamma(red);
	green = linear_to_gamma(green);
	blue = linear_to_gamma(blue);
	red = clamp(intensity, red);
	green = clamp(intensity, green);
	blue = clamp(intensity, blue);;
	red *= 255.0;
	green *= 255.0;
	blue *= 255.0;
	return ((t_vec3){red, green, blue});
}

void	write_color(t_vec3 color_vec)
{
	ft_printf("%d %d %d\n", \
			(int)color_vec.x, (int)color_vec.y, (int)color_vec.z);
}
