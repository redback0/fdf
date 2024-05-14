/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 23:38:37 by njackson          #+#    #+#             */
/*   Updated: 2024/05/14 18:25:49 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char *argv[])
{
	t_fdf_dat	dat;

	if (argc != 2)
		return (0); // PRINT ERROR
	dat.mlx = mlx_init();
	dat.height = 600;
	dat.width = 800;
	dat.img = mlx_new_image(dat.mlx, dat.width, dat.height);
	dat.img_dat = (unsigned int *)mlx_get_data_addr(dat.img,
			&dat.bpp, &dat.sl, &dat.endian);
	dat.img_size = (dat.sl / (dat.bpp / 8)) * dat.height;
	ft_log(1, "IMAGE INFO\nbpp: %d\nsize_line: %d\nendian: %d\nimg_size: %d\n",
		dat.bpp, dat.sl, dat.endian, dat.img_size);
	dat.win = mlx_new_window(dat.mlx, dat.width, dat.height, "");
	get_map(argv[1], &dat);
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
		map_free(dat);
		vertex_map_free(dat->v_map, dat);
		mlx_destroy_window(dat->mlx, dat->win);
		exit(0);
	}
	return (0);
}

void	get_vertex_map(t_fdf_dat *dat)
{
	int			xi;
	int			yi;
	int			scale;

	scale = 25;
	xi = 0;
	while (xi < dat->map_x)
	{
		yi = 0;
		while (yi < dat->map_y)
		{
			dat->v_map[xi][yi].x = ((xi - yi) / sqrt(2))
				* scale + (dat->width / 2);
			dat->v_map[xi][yi].y = ((xi + (2 * dat->map[xi][yi]) + yi) / sqrt(6))
				* scale + (dat->height / 2);
			yi++;
		}
		xi++;
	}
}

int	redraw(t_fdf_dat *dat)
{
	int			xi;
	int			yi;
	int			img_i;

	ft_log(1, "REDRAW\n");
	get_vertex_map(dat);
	// WRITE ALL ELEMENTS OF dat->v_map TO IMAGE
	xi = 0;
	while (xi < dat->map_x)
	{
		yi = 0;
		while (yi < dat->map_y)
		{
			if (dat->v_map[xi][yi].y < dat->height
				&& dat->v_map[xi][yi].x < dat->width)
			{
				img_i = dat->v_map[xi][yi].y * dat->width + dat->v_map[xi][yi].x;
				dat->img_dat[img_i] = 0x00ffffff;
			}
			yi++;
		}
		xi++;
	}
	mlx_put_image_to_window(dat->mlx, dat->win, dat->img, 0, 0);
	return (0);
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
