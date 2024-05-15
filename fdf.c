/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 23:38:37 by njackson          #+#    #+#             */
/*   Updated: 2024/05/15 21:10:34 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char *argv[])
{
	t_fdf_dat	dat;

	if (argc != 2)
		return (ft_log(0, "USAGE: ./fdf MAP.fdf\n"), 0);
	init_fdf_dat(&dat);
	get_map(argv[1], &dat);
	get_vertex_map(&dat);
	redraw(&dat);
	mlx_put_image_to_window(dat.mlx, dat.win, dat.img, 0, 0);
	mlx_key_hook(dat.win, &on_key_pressed, &dat);
	ft_log(1, "STARTING LOOP\n");
	mlx_loop(dat.mlx);
}

void	init_fdf_dat(t_fdf_dat *dat)
{
	dat->mlx = mlx_init();
	dat->height = 600;
	dat->width = 800;
	dat->x_shift = 0;
	dat->y_shift = 0;
	dat->scale = 20.0;
	dat->img = mlx_new_image(dat->mlx, dat->width, dat->height);
	dat->img_dat = (unsigned int *)mlx_get_data_addr(dat->img,
			&dat->bpp, &dat->sl, &dat->endian);
	dat->img_size = (dat->sl / (dat->bpp / 8)) * dat->height;
	ft_log(1, "IMAGE INFO\nbpp: %d\nsize_line: %d\nendian: %d\nimg_size: %d\n",
		dat->bpp, dat->sl, dat->endian, dat->img_size);
	dat->win = mlx_new_window(dat->mlx, dat->width, dat->height, "");
}

void	shift_scale_screen(int keycode, t_fdf_dat *dat)
{
	if (keycode == K_RIGHT_ARROW)
		dat->x_shift -= 50;
	else if (keycode == K_UP_ARROW)
		dat->y_shift += 50;
	else if (keycode == K_LEFT_ARROW)
		dat->x_shift += 50;
	else if (keycode == K_DOWN_ARROW)
		dat->y_shift -= 50;
	else if (keycode == K_PLUS)
	{
		dat->scale *= 1.2;
		get_vertex_map(dat);
	}
	else if (keycode == K_MINUS)
	{
		dat->scale *= 0.8;
		get_vertex_map(dat);
	}
	redraw(dat);
}

int	on_key_pressed(int keycode, t_fdf_dat *dat)
{
	ft_log(1, "KEY PRESSED: %x\n", keycode);
	if (keycode == ESCAPE)
	{
		map_free(dat);
		vertex_map_free(dat);
		mlx_destroy_window(dat->mlx, dat->win);
		exit(0);
	}
	else if (keycode == K_RIGHT_ARROW || keycode == K_UP_ARROW
		|| keycode == K_LEFT_ARROW || keycode == K_DOWN_ARROW
		|| keycode == K_PLUS || keycode == K_MINUS)
		shift_scale_screen(keycode, dat);
	return (0);
}

void	get_vertex_map(t_fdf_dat *dat)
{
	int			xi;
	int			yi;

	xi = 0;
	while (xi < dat->map_x)
	{
		yi = 0;
		while (yi < dat->map_y)
		{
			ft_log(3, "CREATING VERTEX (%d, %d)\n", xi, yi);
			dat->v_map[xi][yi].x = (((xi - dat->map_x / 2) * dat->scale
						- -(yi - dat->map_y / 2) * dat->scale)
					/ sqrt(2)) + (dat->width / 2);
			dat->v_map[xi][yi].y = (((xi - dat->map_x / 2) * dat->scale
						+ (2 * -dat->map[xi][yi].z) * dat->scale
						+ -(yi - dat->map_y / 2) * dat->scale)
					/ sqrt(6)) + (dat->height / 2);
			yi++;
		}
		xi++;
	}
}
