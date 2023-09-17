/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 17:05:37 by vparlak           #+#    #+#             */
/*   Updated: 2023/09/17 19:04:29 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h> // silmeyi unutma

void	ft_draw(t_vars *vars)
{
	t_point	point_1;
	t_point	point_2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < vars->map.ordinate)
	{
		j = 0;
		while (j < vars->map.axis)
		{
			printf("%d,0x%X ", vars->map.points[j][i].z,
				vars->map.points[j][i].color);
			j++;
		}
		printf("\n");
		i++;
	}
	point_1.x = 100;
	point_1.y = 100;
	point_2.x = 150;
	point_2.y = 100;
	ft_draw_line(point_1, point_2, vars);
}
