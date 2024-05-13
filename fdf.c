/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 23:38:37 by njackson          #+#    #+#             */
/*   Updated: 2024/05/13 14:47:05 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(void)
{
	t_fdf_dat	dat;

	dat.mlx = mlx_init();
	dat.win_height = 600;
	dat.win_width = 800;
	dat.win = mlx_new_window(dat.mlx, dat.win_width, dat.win_height, "");
	mlx_key_hook(dat.win, &key_hook, &dat);
	ft_log(3, "STARTING LOOP\n");
	mlx_loop(dat.mlx);
}

int	key_hook(int keycode, t_fdf_dat *dat)
{
	ft_log(3, "KEY PRESSED: %x\n", keycode);
	if (keycode == ESCAPE)
	{
		mlx_destroy_window(dat->mlx, dat->win);
		exit(0);
	}
	return (0);
}
