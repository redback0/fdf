/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 00:11:50 by njackson          #+#    #+#             */
/*   Updated: 2024/05/14 14:59:52 by njackson         ###   ########.fr       */
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
#  define ESCAPE	0xff1b
#  define K_A		0x61

# else
// FOR OpenGL
#  define ESCAPE	0x35
#  define K_A		0x0
# endif

typedef struct s_fdf_dat
{
	void			*mlx;
	void			*win;
	void			*img;
	unsigned int	*img_dat;
	int				img_size;
	int				height;
	int				width;
	int				bpp;
	int				sl;
	int				endian;
}	t_fdf_dat;

int		on_key_pressed(int keycode, t_fdf_dat *dat);
int		redraw(t_fdf_dat *dat);

#endif
