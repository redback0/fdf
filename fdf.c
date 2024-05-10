/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 23:38:37 by njackson          #+#    #+#             */
/*   Updated: 2024/05/11 00:14:41 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(void)
{
	t_fdf_dat	dat;

	dat.mlx = mlx_init();
	dat.win = mlx_new_window(dat.mlx, 800, 600, "");
	mlx_key_hook(dat.win, &key_hook, &dat);
	ft_log(3, "STARTING LOOP\n");
	mlx_loop(dat.mlx);
}

int	key_hook(int keycode, t_fdf_dat *dat)
{
	ft_log(3, "KEY PRESSED\n");
	if (keycode == 0xff1b)
	{
		mlx_destroy_window(dat->mlx, dat->win);
		mlx_loop_end(dat->mlx);
	}
	return (0);
}
