/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 23:38:37 by njackson          #+#    #+#             */
/*   Updated: 2024/05/14 15:42:17 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(void)
{
	t_fdf_dat	dat;

	dat.mlx = mlx_init();
	dat.height = 600;
	dat.width = 800;
	dat.img = mlx_new_image(dat.mlx, dat.width, dat.height);
	dat.img_dat = (unsigned int *)mlx_get_data_addr(dat.img,
			&dat.bpp, &dat.sl, &dat.endian);
	dat.img_size = (dat.sl / (dat.bpp / 8)) * dat.height;
	ft_log(1, "bpp: %d\nsize_line: %d\nendian: %d\nimg_size: %d\n",
		dat.bpp, dat.sl, dat.endian, dat.img_size);
	dat.win = mlx_new_window(dat.mlx, dat.width, dat.height, "");
	redraw(&dat);
	mlx_put_image_to_window(dat.mlx, dat.win, dat.img, 0, 0);
	mlx_key_hook(dat.win, &on_key_pressed, &dat);
	ft_log(1, "STARTING LOOP\n");
	mlx_loop(dat.mlx);
}

int	on_key_pressed(int keycode, t_fdf_dat *dat)
{
	ft_log(1, "KEY PRESSED: %x\n", keycode);
	if (keycode == ESCAPE)
	{
		mlx_destroy_window(dat->mlx, dat->win);
		exit(0);
	}
	return (0);
}

int	redraw(t_fdf_dat *dat)
{
	double	size = 50;
	double	cube[][3] = {{0, 0, 0}, {0, 0, size}, {0, size, 0}, {0, size, size},
			{size, 0, 0}, {size, 0, size}, {size, size, 0}, {size, size, size}};
	int		x;
	int		y;
	int		i;

	ft_log(1, "REDRAW\n");
	// CHANGE IMAGE HERE
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
	mlx_put_image_to_window(dat->mlx, dat->win, dat->img, 0, 0);
	return (0);
}
// ISOMETRIC CALCULATION
// x' = (x - z) / sqrt(2)
// y' = (x + 2y + z) / sqrt(6)
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
