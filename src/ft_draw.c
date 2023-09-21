/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 17:05:37 by vparlak           #+#    #+#             */
/*   Updated: 2023/09/21 00:45:49 by vparlak          ###   ########.fr       */
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

t_point	ft_rotation_2d(t_point p1, t_point origin, int teta)
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
	t_render_map **map;
	 int angle = 30;
		t_point	p1;
	t_point	p2;
	t_point point;
	int		x;
	int		y;

	vars->origin.x = ((WIDTH - ((vars->map.axis + vars->map.ordinate) * vars->x_offset)) / 2) + (vars->x_offset * vars->map.ordinate);
	vars->origin.y = ((HEIGHT - ((vars->map.axis + vars->map.ordinate) * vars->y_offset)) / 2) + (vars->y_offset);
	vars->origin.x += vars->i;

	map = ft_calloc(vars->map.axis, sizeof(t_render_map *));
	// if map yoksa leak kontrol
	x = 0;
	while (x < vars->map.axis)
	{
		map[x] = ft_calloc(vars->map.ordinate, sizeof(t_render_map));
		//if her map için leak kontolü
		x++;
	}
	x = 0;
	while (x < vars->map.axis)
	{
		y = 0;
		while (y < vars->map.ordinate)
		{
			map[x][y].x = (x * vars->offset) + vars->origin.x;
			map[x][y].y = (y * vars->offset) + vars->origin.y;
			map[x][y].z = (vars->map.points[x][y].z * vars->offset);
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
			point.x = map[x][y].x;
			point.y = map[x][y].y;
			point = ft_rotation_2d(point, vars->origin, angle);
			map[x][y].x = point.x;
			map[x][y].y = point.y;
			y++;
		}
		x++;
	}
	x = 0;
	while (x < vars->map.axis)
	{
		y = 0;
		vars->origin.x = map[x][y].x;
		vars->origin.y = map[x][y].y;
		while (y < vars->map.ordinate)
		{
			point.x = map[x][y].x;
			point.y = map[x][y].y;
			point = ft_rotation_2d(point, vars->origin,  (180 - (90 + angle)) - angle );
			map[x][y].x = point.x;
			map[x][y].y = point.y - map[x][y].z;
			//mlx_pixel_put(vars->m.mlx, vars->m.win, round(map[x][y].x), round(map[x][y].y), 0x00FFFFFF);
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
			p1.x = map[x - 1][y - 1].x;
			p1.y = map[x - 1][y - 1].y;
			p2.x = map[x][y - 1].x;
			p2.y = map[x][y - 1].y;
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

			p1.x = map[x - 1][y - 1].x;
			p1.y = map[x - 1][y - 1].y;
			p2.x = map[x - 1][y].x;
			p2.y = map[x - 1][y].y;
			ft_draw_line(p1, p2, vars);
			y++;
		}
		x++;
	}
}





