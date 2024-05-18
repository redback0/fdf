/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 22:32:33 by njackson          #+#    #+#             */
/*   Updated: 2024/05/18 23:28:57 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	shift_screen(int keycode, t_fdf_dat *dat)
{
	if (keycode == K_RIGHT_ARROW)
		dat->x_shift -= 50;
	else if (keycode == K_UP_ARROW)
		dat->y_shift += 50;
	else if (keycode == K_LEFT_ARROW)
		dat->x_shift += 50;
	else if (keycode == K_DOWN_ARROW)
		dat->y_shift -= 50;
	redraw(dat);
}

void	rotate_screen(int keycode, t_fdf_dat *dat)
{
	if (keycode == K_A)
		dat->za -= M_PI / 16;
	else if (keycode == K_D)
		dat->za += M_PI / 16;
	else if (keycode == K_W)
		dat->xa += M_PI / 16;
	else if (keycode == K_S)
		dat->xa -= M_PI / 16;
	if (dat->za >= 2 * M_PI)
		dat->za -= 2 * M_PI;
	else if (dat->za < 0)
		dat->za += 2 * M_PI;
	if (dat->xa > M_PI)
		dat->xa = M_PI;
	else if (dat->xa < 0)
		dat->xa = 0;
	rotate_z(dat);
	rotate_x(dat);
	redraw(dat);
}

void	scale_screen(int keycode, t_fdf_dat *dat)
{
	if (keycode == K_PLUS)
	{
		dat->x_shift *= 1.2;
		dat->y_shift *= 1.2;
		dat->scale *= 1.2;
	}
	else if (keycode == K_MINUS)
	{
		dat->x_shift *= 0.8;
		dat->y_shift *= 0.8;
		dat->scale *= 0.8;
	}
	rotate_z(dat);
	rotate_x(dat);
	redraw(dat);
}
