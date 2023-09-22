/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 15:51:20 by vparlak           #+#    #+#             */
/*   Updated: 2023/09/22 03:49:34 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void	**ft_free_map_point(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->map.axis)
	{
		free((vars->map.points)[i]);
		i++;
	}
	free(vars->map.points);
	return (NULL);
}

void	**ft_free_r_map(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->map.axis)
	{
		free((vars->r_map)[i]);
		i++;
	}
	free(vars->r_map);
	return (NULL);
}

char	**ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

void	ft_file_close(int fd, t_vars *vars)
{
	if (close(fd) == -1)
	{
		if (vars != NULL)
			ft_free_map_point(vars);
		perror("File close error");
		exit(EXIT_FAILURE);
	}
}

void	ft_error(char *msg, t_vars *vars, char **splitted_str, int status)
{
	perror(msg);
	if (vars != NULL && status == 0)
		ft_free_map_point(vars);
	if (vars != NULL && status == 1)
	{
		ft_free_map_point(vars);
		ft_free_r_map(vars);
	}
	if (splitted_str != NULL)
		ft_free_tab(splitted_str);
	exit(EXIT_FAILURE);
}
