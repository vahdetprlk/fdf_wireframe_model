/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 15:05:34 by vparlak           #+#    #+#             */
/*   Updated: 2023/09/18 17:52:41 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int	ft_count_axis(char *line)
{
	int		axis;
	char	**splitted_line;

	splitted_line = ft_split(line, ' ');
	if (!splitted_line)
		ft_error("Malloc error", NULL, NULL);
	axis = 0;
	while (splitted_line[axis] != NULL)
		axis++;
	ft_free_tab(splitted_line);
	return (axis);
}

static int	ft_find_axis(char *file, int *fd)
{
	int		axis;
	char	*first_line;

	*fd = open(file, O_RDONLY);
	if (*fd < 0)
		ft_error("File open error", NULL, NULL);
	first_line = get_next_line(*fd);
	if (!first_line)
		ft_error("File reading error", NULL, NULL);
	axis = ft_count_axis(first_line);
	free(first_line);
	return (axis);
}

static int	ft_find_ordinate(int fd, int axis)
{
	int		ordinate;
	char	*line;

	line = get_next_line(fd);
	if (!line)
		ft_error("File reading error", NULL, NULL);
	ft_check_axis(line, axis);
	ordinate = 2;
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
		ft_check_axis(line, axis);
		ordinate++;
	}
	ft_file_close(fd, NULL);
	return (ordinate);
}

static void	ft_init_map(t_vars *vars, char *file)
{
	int	i;

	vars->map.points = malloc(sizeof(t_point_arr *) * vars->map.axis);
	if (!vars->map.points)
		ft_error("Malloc error", NULL, NULL);
	i = 0;
	while (i < vars->map.axis)
	{
		vars->map.points[i] = malloc(sizeof(t_point_arr) * vars->map.ordinate);
		if (!vars->map.points[i])
			ft_error("Malloc error", vars, NULL);
		i++;
	}
	ft_read_map(vars, file);
}

void	ft_check_map(char *file, t_vars *vars)
{
	int	fd;

	vars->map.axis = ft_find_axis(file, &fd);
	vars->map.ordinate = ft_find_ordinate(fd, vars->map.axis);
	ft_init_map(vars, file);
}
