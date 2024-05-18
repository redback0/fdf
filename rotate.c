/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:28:19 by njackson          #+#    #+#             */
/*   Updated: 2024/05/18 21:26:58 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Rotation around axis z with angle a, as an example is:
// x = x * cos(a) - y * sin(a)
// y = y * cos(a) - x * sin(a)
// z = z

void	reset_angle(t_fdf_dat *dat)
{
	int	xi;
	int	yi;

	xi = 0;
	while (xi < dat->map_x)
	{
		yi = 0;
		while (yi < dat->map_y)
		{
			dat->v_map[xi][yi].color = dat->map[xi][yi].color;
			yi++;
		}
		xi++;
	}
}

void	rotate_z(t_fdf_dat *dat)
{
	double	sinza;
	double	cosza;
	int		xi;
	int		yi;

	sinza = sin(dat->za);
	cosza = cos(dat->za);
	xi = 0;
	while (xi < dat->map_x)
	{
		yi = 0;
		while (yi < dat->map_y)
		{
			dat->v_map[xi][yi].x = xi * cosza * dat->scale
				- yi * sinza * dat->scale + dat->width / 2;
			dat->v_map[xi][yi].y = yi * cosza * dat->scale
				+ xi * sinza * dat->scale + dat->height / 2;
			yi++;
		}
		xi++;
	}
}

void	rotate_x(t_fdf_dat *dat)
{
	double	sinxa;
	double	cosxa;
	int		xi;
	int		yi;

	sinxa = sin(dat->xa);
	cosxa = cos(dat->xa);
	xi = 0;
	while (xi < dat->map_x)
	{
		yi = 0;
		while (yi < dat->map_y)
		{
			dat->v_map[xi][yi].y = dat->v_map[xi][yi].y * cosxa
				- dat->map[xi][yi].z * sinxa * dat->scale;
			yi++;
		}
		xi++;
	}
}
