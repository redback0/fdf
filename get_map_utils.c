/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:54:12 by njackson          #+#    #+#             */
/*   Updated: 2024/05/15 21:00:48 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

unsigned int	get_map_ele_color(char *str)
{
	char	*cstr;

	cstr = ft_strchr(str, ',');
	if (cstr != 0)
		return (ft_atou_base(cstr + 3, HEX_LOWER));
	return (0xffffff);
}
