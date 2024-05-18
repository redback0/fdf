/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 23:38:37 by njackson          #+#    #+#             */
/*   Updated: 2024/05/18 21:19:29 by njackson         ###   ########.fr       */
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
	reset_angle(&dat);
	rotate_z(&dat);
	rotate_x(&dat);
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
	dat->za = M_PI/4;
	dat->xa = M_PI/4;
	dat->img = mlx_new_image(dat->mlx, dat->width, dat->height);
	dat->img_dat = (unsigned int *)mlx_get_data_addr(dat->img,
			&dat->bpp, &dat->sl, &dat->endian);
	dat->img_size = (dat->sl / (dat->bpp / 8)) * dat->height;
	ft_log(1, "IMAGE INFO\nbpp: %d\nsize_line: %d\nendian: %d\nimg_size: %d\n",
		dat->bpp, dat->sl, dat->endian, dat->img_size);
	dat->win = mlx_new_window(dat->mlx, dat->width, dat->height, "");
}

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

void	scale_rotate_screen(int keycode, t_fdf_dat *dat)
{
	if (keycode == K_PLUS)
		dat->scale *= 1.2;
	else if (keycode == K_MINUS)
		dat->scale *= 0.8;
	else if (keycode == K_A)
		dat->za -= M_PI/16;
	else if (keycode == K_D)
		dat->za += M_PI/16;
	else if (keycode == K_W)
		dat->xa += M_PI/16;
	else if (keycode == K_S)
		dat->xa -= M_PI/16;
	rotate_z(dat);
	rotate_x(dat);
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
		|| keycode == K_LEFT_ARROW || keycode == K_DOWN_ARROW)
		shift_screen(keycode, dat);
	else if (keycode == K_PLUS || keycode == K_MINUS
		|| keycode == K_A || keycode == K_D
		|| keycode == K_W || keycode == K_S)
		scale_rotate_screen(keycode, dat);
	return (0);
}
