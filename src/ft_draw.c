/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 17:05:37 by vparlak           #+#    #+#             */
/*   Updated: 2023/09/21 17:26:39 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdlib.h>
#include "mlx.h"
#include <stdio.h>

void	orjin_delta(t_point *point, int orjin_x, int orjin_y)
{
	point->x = point->x + orjin_x;
	point->y = point->y + orjin_y;
}

t_point	ft_rotation_2d(t_point p1, t_point origin, int teta) //z-axis
{
	t_point	tmp_point;

	teta %= 360;
	p1.x = p1.x - origin.x;
	p1.y = p1.y - origin.y;
	tmp_point.x = (p1.x * cos(teta * (M_PI / 180)))
		- (p1.y * sin(teta * (M_PI / 180)));
	tmp_point.y = (p1.x * sin(teta * (M_PI / 180)))
		+ (p1.y * cos(teta * (M_PI / 180)));
	tmp_point.x = tmp_point.x + origin.x;
	tmp_point.y = tmp_point.y + origin.y;
	return (tmp_point);
}



void	ft_draw(t_vars *vars)
{
	int				angle;
	t_point			p1;
	t_point			p2;
	t_point			point;
	int				x;
	int				y;

	angle = 30;
	vars->origin.x = ((WIDTH - ((vars->map.axis + vars->map.ordinate) * vars->x_offset)) / 2) + (vars->x_offset * vars->map.ordinate);
	vars->origin.y = ((HEIGHT - ((vars->map.axis + vars->map.ordinate) * vars->y_offset)) / 2) + (vars->y_offset);
	vars->origin.x += vars->i;
	vars->origin.y += vars->j;
	x = 0;
	while (x < vars->map.axis)
	{
		y = 0;
		while (y < vars->map.ordinate)
		{
			vars->r_map[x][y].x = (x * vars->offset) + vars->origin.x;
			vars->r_map[x][y].y = (y * vars->offset) + vars->origin.y;
			vars->r_map[x][y].z = (vars->map.points[x][y].z * vars->offset);
			y++;
		}
		x++;
	}
	x = 0;
	while (x < vars->map.axis)
	{
		y = 0;
		while (y < vars->map.ordinate)
		{
			point.x = vars->r_map[x][y].x;
			point.y = vars->r_map[x][y].y;
			point = ft_rotation_2d(point, vars->origin, angle);
			vars->r_map[x][y].x = point.x;
			vars->r_map[x][y].y = point.y;
			y++;
		}
		x++;
	}
	x = 0;
	while (x < vars->map.axis)
	{
		y = 0;
		vars->origin.x = vars->r_map[x][y].x;
		vars->origin.y = vars->r_map[x][y].y;
		while (y < vars->map.ordinate)
		{
			point.x = vars->r_map[x][y].x;
			point.y = vars->r_map[x][y].y;
			point = ft_rotation_2d(point, vars->origin,  (180 - (90 + angle)) - angle );
			vars->r_map[x][y].x = point.x;
			vars->r_map[x][y].y = point.y - vars->r_map[x][y].z;
			y++;
		}
		x++;
	}
	y = 1;
	while (y <= vars->map.ordinate)
	{
		x = 1;
		while (x < vars->map.axis)
		{
			p1.x = vars->r_map[x - 1][y - 1].x;
			p1.y = vars->r_map[x - 1][y - 1].y;
			p2.x = vars->r_map[x][y - 1].x;
			p2.y = vars->r_map[x][y - 1].y;
			ft_draw_line(p1, p2, vars);
			x++;
		}
		y++;
	}
	x = 1;
	while (x <= vars->map.axis)
	{
		y = 1;
		while (y < vars->map.ordinate)
		{
			p1.x = vars->r_map[x - 1][y - 1].x;
			p1.y = vars->r_map[x - 1][y - 1].y;
			p2.x = vars->r_map[x - 1][y].x;
			p2.y = vars->r_map[x - 1][y].y;
			ft_draw_line(p1, p2, vars);
			y++;
		}
		x++;
	}
}
