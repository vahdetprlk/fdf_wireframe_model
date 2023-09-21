/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 15:23:41 by vparlak           #+#    #+#             */
/*   Updated: 2023/09/21 23:24:01 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line.h"

int	ft_count_axis(char *line)
{
	int		axis;
	char	**splitted_line;

	splitted_line = ft_split(line, ' ');
	if (!splitted_line)
	{
		free(line);
		ft_error("Malloc error", NULL, NULL, 0);
	}
	axis = 0;
	while (splitted_line[axis] != NULL)
		axis++;
	ft_free_tab(splitted_line);
	return (axis);
}

void	ft_check_axis(char *line, int axis)
{
	if (axis != ft_count_axis(line))
	{
		write(2, "Map dimension error\n", 20);
		free(line);
		exit(EXIT_FAILURE);
	}
}

static void	ft_map_read_loop(int fd, int y, t_vars *vars)
{
	char	*line;
	char	**splitted_line;
	char	**point;
	int		x;

	line = get_next_line(fd);
	if (!line)
		ft_error("File reading error", vars, NULL, 0);
	splitted_line = ft_split(line, ' ');
	free(line);
	if (!splitted_line)
		ft_error("Malloc error", vars, NULL, 0);
	x = 0;
	while (x < vars->map.axis)
	{
		point = ft_split(splitted_line[x], ',');
		if (!point)
			ft_error("Malloc error", vars, splitted_line, 0);
		vars->map.points[x][y].z = ft_atoi(point[0]);
		vars->map.points[x][y].color = ft_atoi_hex(point[1]);
		ft_free_tab(point);
		x++;
	}
	ft_free_tab(splitted_line);
}

void	ft_read_map(t_vars *vars, char *file)
{
	int		fd;
	int		y;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error("File open error", vars, NULL, 0);
	y = 0;
	while (y < vars->map.ordinate)
	{
		ft_map_read_loop(fd, y, vars);
		y++;
	}
	ft_file_close(fd, vars);
}
