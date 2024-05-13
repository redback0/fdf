/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 00:11:50 by njackson          #+#    #+#             */
/*   Updated: 2024/05/13 12:45:07 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# ifdef _LINUX
#  define ESCAPE 0xff1b
# else
#  define ESCAPE 0x35
# endif

typedef struct s_fdf_dat
{
	void	*mlx;
	void	*win;
} t_fdf_dat;

int	key_hook(int keycode, t_fdf_dat *dat);

#endif
