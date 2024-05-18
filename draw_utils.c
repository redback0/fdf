/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 22:01:54 by njackson          #+#    #+#             */
/*   Updated: 2024/05/18 22:15:56 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	redraw_pos(t_fdf_dat *dat)
{
	int	xi;
	int	yi;

	xi = 0;
	while (xi < dat->map_x)
	{
		yi = 0;
		while (yi < dat->map_y)
		{
			ft_log(3, "DRAWING VERTEX (%d, %d) (%d, %d)\n", xi, yi,
				dat->v_map[xi][yi].x, dat->v_map[xi][yi].y);
			if (xi > 0)
				draw_line(dat->v_map[xi][yi], dat->v_map[xi - 1][yi], dat);
			if (yi > 0)
				draw_line(dat->v_map[xi][yi], dat->v_map[xi][yi - 1], dat);
			yi++;
		}
		xi++;
	}
	mlx_put_image_to_window(dat->mlx, dat->win, dat->img, 0, 0);
}

void	redraw_neg(t_fdf_dat *dat)
{
	int	xi;
	int	yi;

	xi = dat->map_x - 1;
	while (xi >= 0)
	{
		yi = dat->map_y - 1;
		while (yi >= 0)
		{
			ft_log(3, "DRAWING VERTEX (%d, %d) (%d, %d)\n", xi, yi,
				dat->v_map[xi][yi].x, dat->v_map[xi][yi].y);
			if (xi > 0)
				draw_line(dat->v_map[xi][yi], dat->v_map[xi - 1][yi], dat);
			if (yi > 0)
				draw_line(dat->v_map[xi][yi], dat->v_map[xi][yi - 1], dat);
			yi--;
		}
		xi--;
	}
	mlx_put_image_to_window(dat->mlx, dat->win, dat->img, 0, 0);
}
