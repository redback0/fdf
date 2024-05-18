/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 22:15:55 by njackson          #+#    #+#             */
/*   Updated: 2024/05/18 21:36:14 by njackson         ###   ########.fr       */
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
	t_color	out;

	out.r = a.r + b.r;
	out.g = a.g + b.g;
	out.b = a.b + b.b;
	return (out);
}

unsigned int	get_color(t_color c)
{
	unsigned int	out;

	out = c.r;
	out = out * 256 + c.g;
	out = out * 256 + c.b;
	return (out);
}
