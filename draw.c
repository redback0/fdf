/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:26:15 by njackson          #+#    #+#             */
/*   Updated: 2024/05/20 13:32:39 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	write_pixel(t_vertex pxl, t_fdf_dat *dat)
{
	int	img_i;

	if (pxl.y + dat->y_shift < dat->height
		&& pxl.x + dat->x_shift < dat->width
		&& pxl.y + dat->y_shift >= 0
		&& pxl.x + dat->x_shift >= 0)
	{
		img_i = (pxl.y + dat->y_shift) * dat->width
			+ dat->width - pxl.x + dat->x_shift;
		dat->img_dat[img_i] = get_color(pxl.color);
	}
}

void	y_draw_line(t_vertex fp, t_vertex sp, t_vertex delta, t_fdf_dat *dat)
{
	t_vertex	pxl;
	t_color		delta_color;
	double		slope;

	slope = delta.x / (double)delta.y;
	pxl.y = fp.y;
	pxl.color = fp.color;
	delta_color = get_delta_color(fp.color, sp.color, -ft_abs(delta.y));
	while (pxl.y != sp.y)
	{
		pxl.x = slope * (pxl.y - fp.y) + fp.x;
		pxl.color = add_color(pxl.color, delta_color);
		write_pixel(pxl, dat);
		pxl.y += (sp.y > fp.y) + -(sp.y < fp.y);
	}
	pxl.x = slope * (pxl.y - fp.y) + fp.x;
	write_pixel(pxl, dat);
}

void	x_draw_line(t_vertex fp, t_vertex sp, t_vertex delta, t_fdf_dat *dat)
{
	t_vertex	pxl;
	t_color		delta_color;
	double		slope;

	slope = delta.y / (double)delta.x;
	pxl.x = fp.x;
	pxl.color = fp.color;
	delta_color = get_delta_color(fp.color, sp.color, -ft_abs(delta.x));
	while (pxl.x != sp.x)
	{
		pxl.y = slope * (pxl.x - fp.x) + fp.y;
		pxl.color = add_color(pxl.color, delta_color);
		write_pixel(pxl, dat);
		pxl.x += (sp.x > fp.x) + -(sp.x < fp.x);
	}
	pxl.y = slope * (pxl.x - fp.x) + fp.y;
	write_pixel(pxl, dat);
}

void	draw_line(t_vertex fp, t_vertex sp, t_fdf_dat *dat)
{
	t_vertex	delta;

	if ((fp.x < -dat->x_shift && sp.x < -dat->x_shift)
		|| (fp.x > dat->width - dat->x_shift
			&& sp.x > dat->width - dat->x_shift)
		|| (fp.y < -dat->y_shift && sp.y < -dat->y_shift)
		|| (sp.y > dat->height - dat->y_shift
			&& sp.y > dat->height - dat->y_shift))
	{
		ft_log(3, "skipping render: off screen\n");
		return ;
	}
	ft_log(3, "color: 0x%x - 0x%x\n", get_color(fp.color), get_color(sp.color));
	delta.x = sp.x - fp.x;
	delta.y = sp.y - fp.y;
	if (ft_abs(delta.y) < ft_abs(delta.x))
	{
		ft_log(3, "render with x\n");
		x_draw_line(fp, sp, delta, dat);
	}
	else
	{
		ft_log(3, "render with y\n");
		y_draw_line(fp, sp, delta, dat);
	}
}

void	redraw(t_fdf_dat *dat)
{
	ft_log(1, "REDRAW\n");
	ft_bzero(dat->img_dat, dat->img_size * sizeof(int));
	if (dat->za < M_PI)
		redraw_pos(dat);
	else
		redraw_neg(dat);
}

// x' = (x - z) / sqrt(2)
// y' = (x + 2y + z) / sqrt(6)

//dat->img_dat[y * dat->width + x]

// CUBE POINTS
/*
   double	size = 50;
   double	cube[][3] = {{0, 0, 0}, {0, 0, size}, {0, size, 0}, {0, size, size},
   {size, 0, 0}, {size, 0, size}, {size, size, 0}, {size, size, size}};
   i = 0;
   while (i < 8)
   {
   x = (cube[i][0] - cube[i][2]) / sqrt(2) + (dat->width / 2);
   y = (cube[i][0] + (2 * cube[i][1]) + cube[i][2]) / sqrt(6)
   + (dat->height / 2);
   dat->img_dat[y * dat->width + x] = 0x00ffffff;
   ft_log(1, "x: %d\ny: %d\n", x, y);
   i++;
   }
 */

// ISOMETRIC CALCULATION
// A cross from corner to corner, colors red at the top, to cyan at the bottom
/*
   d = (double)dat->height / (double)dat->width;
   red = 255.0 / dat->height;
   x = 0;
   while (x < dat->width)
   {
   res[0] = (int)(d * x);
   res[1] = (int)(-d * x) + dat->height;
   y = 0;
   while (y < dat->height)
   {
   if (y == res[0] || y == res[1])
   dat->img_dat[y * dat->width + x] = ((int)(red
 * (dat->height - y)) * 0x00010000)
 + ((int)(red * y) * 0x00000101);
 else
 dat->img_dat[y * dat->width + x] = 0;
 y++;
 }
 x++;
 }
 */
