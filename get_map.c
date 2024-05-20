/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42adel.o>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:13:54 by njackson          #+#    #+#             */
/*   Updated: 2024/05/20 14:45:04 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_map(char *file, t_fdf_dat *dat)
{
	char	*line;
	int		fd;
	int		i;

	get_map_line_info(file, dat);
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		line[ft_strlen(line) - 1] = 0;
		if (get_map_line(ft_split(line, ' '), i++, dat))
			return (1);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

int	get_map_line(char **split, int i, t_fdf_dat *dat)
{
	int	j;

	j = -1;
	ft_log(3, "GETTING LINE: %d\n", i);
	while (split[++j])
		;
	if (!dat->map_y)
		dat->map_y = j;
	else if (dat->map_y != j)
	{
		dat->map_x = i;
		map_free(dat);
		vertex_map_free(dat);
		ft_split_free(split, free);
		return (ft_log(3, "BAD AMOUNT OF WORDS ON LINE\n"), 1);
	}
	dat->map[i] = (t_fdf_map_ele *)malloc(dat->map_y * sizeof(t_fdf_map_ele));
	dat->v_map[i] = (t_vertex *)malloc(dat->map_y * sizeof(t_vertex));
	j = 0;
	while (split[j])
	{
		dat->map[i][j].z = -ft_atoi(split[j]);
		dat->map[i][j].color = get_map_ele_color(split[j]);
		j++;
	}
	ft_split_free(split, free);
	return (0);
}

void	get_map_line_info(char *file, t_fdf_dat *dat)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	dat->map = (t_fdf_map_ele **)malloc(i * sizeof(t_fdf_map_ele *));
	dat->v_map = (t_vertex **)malloc(i * sizeof(t_vertex *));
	dat->map_x = i;
	dat->map_y = 0;
}

void	map_free(t_fdf_dat *dat)
{
	int	i;

	i = 0;
	while (i < dat->map_x)
	{
		free(dat->map[i]);
		i++;
	}
	free(dat->map);
}

void	vertex_map_free(t_fdf_dat *dat)
{
	int	i;

	i = 0;
	while (i < dat->map_x)
	{
		free(dat->v_map[i]);
		i++;
	}
	free(dat->v_map);
}
