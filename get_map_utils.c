/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:54:12 by njackson          #+#    #+#             */
/*   Updated: 2024/05/16 22:46:05 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_color	get_map_ele_color(char *str)
{
	char			*cstr;
	unsigned int	color;
	t_color			out;

	cstr = ft_strchr(str, ',');
	if (cstr != 0)
	{
		color = ft_atou_base(cstr + 3, HEX_UPPER);
		out.b = (unsigned char)color;
		out.g = (unsigned char)(color / 256);
		out.r = (unsigned char)(color / (256 * 256));
		ft_log(3, "got color %s (r: %d, g: %d, b: %d)\n", cstr+1,
			(int)out.r, (int)out.g, (int)out.b);
	}
	else
	{
		out.r = 0xff;
		out.g = 0xff;
		out.b = 0xff;
	}
	return (out);
}
