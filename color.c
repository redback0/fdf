/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 22:15:55 by njackson          #+#    #+#             */
/*   Updated: 2024/05/16 23:42:15 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_color	get_delta_color(t_color scolor, t_color ecolor, int step)
{
	t_color	out;

	out.r = (scolor.r - ecolor.r) / step;
	out.g = (scolor.g - ecolor.g) / step;
	out.b = (scolor.b - ecolor.b) / step;
	return (out);
}

t_color	add_color(t_color a, t_color b)
{
	t_color out;

	out.r = a.r + b.r;
	out.g = a.g + b.g;
	out.b = a.b + b.b;
	return (out);
}

unsigned int	get_color(t_color c)
{
	unsigned int	out;

	if ((int)c.r > 256 || (int)c.r < 0) ft_printf_fd(2, "COLOR SIZE ERROR r: %d\n", (int)c.r);
	if ((int)c.g > 256 || (int)c.g < 0) ft_printf_fd(2, "COLOR SIZE ERROR g: %d\n", (int)c.g);
	if ((int)c.b > 256 || (int)c.b < 0) ft_printf_fd(2, "COLOR SIZE ERROR b: %d\n", (int)c.b);
	out = c.r;
	out = out * 256 + c.g;
	out = out * 256 + c.b;
	return (out);
}
