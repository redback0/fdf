/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42adel.o>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:13:54 by njackson          #+#    #+#             */
/*   Updated: 2024/05/14 17:57:31 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_map(char *file, t_fdf_dat *dat)
{
	char	*line;
	int		fd;
	int		i;

	get_map_line_info(file, dat);
	ft_log(1, "STARTING MAP LOOP\n");
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		get_map_line(ft_split(line, ' '), i++, dat);
		free(line);
		line = get_next_line(fd);
	}
	ft_log(1, "GOT ALL ROWS\n");
	close(fd);
	return (0);
}

int	get_map_line(char **split, int i, t_fdf_dat *dat)
{
	int	j;

	j = -1;
	while (split[++j])
		;
	if (!dat->map_y)
		dat->map_y = j;
	else if (dat->map_y != j)
	{
		dat->map_x = i;
		map_free(dat);
		ft_split_free(split, free);
		return (ft_log(3, "BAD AMOUNT OF WORDS ON LINE\n"), 1);
	}
	dat->map[i] = (int *)malloc(dat->map_y * sizeof(int));
	ft_log(3, "%p\n", dat->map[i]);
	j = 0;
	while (split[j])
	{
		dat->map[i][j] = ft_atoi(split[j]);
		j++;
	}
	ft_split_free(split, free);
	ft_log(1, "GOT ROW\n");
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
	dat->map = (int **)malloc(i * sizeof(int *));
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

void	vertex_map_free(t_vertex **map, t_fdf_dat *dat)
{
	int	i;

	i = 0;
	while (i < dat->map_x)
	{
		free(map[i]);
		i++;
	}
	free(map);
}
