/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 00:11:50 by njackson          #+#    #+#             */
/*   Updated: 2024/05/13 14:46:24 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# ifdef LINUX
// FOR X11
#  define ESCAPE 0xff1b

# else
// FOR OpenGL
#  define ESCAPE 0x35
# endif

typedef struct s_fdf_dat
{
	void	*mlx;
	void	*win;
	int		win_height;
	int		win_width;
}	t_fdf_dat;

int	key_hook(int keycode, t_fdf_dat *dat);

#endif
