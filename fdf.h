/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 00:11:50 by njackson          #+#    #+#             */
/*   Updated: 2024/05/16 22:51:07 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# ifdef LINUX
// FOR X11
#  define ESCAPE		0xff1b
#  define K_LEFT_ARROW	0xff51
#  define K_UP_ARROW	0xff52
#  define K_RIGHT_ARROW	0xff53
#  define K_DOWN_ARROW	0xff54
#  define K_A			0x61
#  define K_W			0x77
#  define K_D			0x64
#  define K_S			0x73
#  define K_PLUS		0x3d
#  define K_MINUS		0x2d

# else
// FOR OpenGL
#  define ESCAPE		0x35
#  define K_LEFT_ARROW	
#  define K_UP_ARROW	
#  define K_RIGHT_ARROW	
#  define K_DOWN_ARROW	
#  define K_A			0x0
#  define K_W			
#  define K_D			
#  define K_S			
# endif

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}	t_color;

// COLOR FUNCTIONS
unsigned int	get_color(t_color c);
t_color			add_color(t_color a, t_color b);
t_color			get_delta_color(t_color scolor, t_color ecolor, int step);


typedef struct s_vertex
{
	int		x;
	int		y;
	t_color	color;
}	t_vertex;

typedef struct s_fdf_map_ele
{
	int		z;
	t_color	color;
}	t_fdf_map_ele;

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
	t_fdf_map_ele	**map;
	int				map_x;
	int				map_y;
	int				x_shift;
	int				y_shift;
	double			scale;
	t_vertex		**v_map;
}	t_fdf_dat;

void			init_fdf_dat(t_fdf_dat *dat);

// GET MAP FUNCTIONS
int				get_map(char *file, t_fdf_dat *dat);
int				get_map_line(char **split, int i, t_fdf_dat *dat);
void			get_map_line_info(char *file, t_fdf_dat *dat);
void			map_free(t_fdf_dat *dat);
void			vertex_map_free(t_fdf_dat *dat);

// UTILS
t_color			get_map_ele_color(char *str);

// EVENT FUNCTIONS
int				on_key_pressed(int keycode, t_fdf_dat *dat);

// SCREEN FUNCTIONS
int				redraw(t_fdf_dat *dat);
void			get_vertex_map(t_fdf_dat *dat);

#endif
