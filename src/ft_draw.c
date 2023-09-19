/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 17:05:37 by vparlak           #+#    #+#             */
/*   Updated: 2023/09/20 02:02:01 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdlib.h>
#include "mlx.h"

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
	int angle = 33;
		t_point	p1;
	t_point	p2;
	t_point point;
	t_point	origin;
	int		x;
	int		y;

	origin.x = ((WIDTH - (vars->offset * (vars->map.axis))) + vars->offset) / 2;
	origin.y = ((HEIGHT - (vars->offset * (vars->map.ordinate))) + vars->offset) / 2;
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
			map[x][y].x = (x * vars->offset) + origin.x;
			map[x][y].y = (y * vars->offset) + origin.y;
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
			point = ft_rotation_2d(point, origin, angle);
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
		origin.x = map[x][y].x;
		origin.y = map[x][y].y;
		while (y < vars->map.ordinate)
		{
			point.x = map[x][y].x;
			point.y = map[x][y].y;
			point = ft_rotation_2d(point, origin,  (180 - (90 + angle)) - angle );
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






/*
void	ft_draw(t_vars *vars)
{
	t_point	p1;
	t_point	p2;
	t_point	origin;
//	t_point relative_origin;
	int		x;
	int		y;

	x = 1;
	y = 1;
	origin.x = ((WIDTH - (vars->offset * (vars->map.axis))) + vars->offset) / 2;
	origin.y = ((HEIGHT - (vars->offset * (vars->map.ordinate))) + vars->offset) / 2;
	while (y <= vars->map.ordinate)
	{
		x = 1;
		while (x < vars->map.axis)
		{
			p1 = ft_rotation_2d(p1, origin, 30);
			p2 = ft_rotation_2d(p2, origin, 30);
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

			p1.x = (x - 1) * vars->offset + origin.x;
			p2.x = (x - 1) * vars->offset + origin.x;
			p1.y = (y - 1) * vars->offset + origin.y;
			p2.y = (y) * vars->offset + origin.y;
			p1 = ft_rotation_2d(p1, origin, 30);
			p2 = ft_rotation_2d(p2, origin, 30);
			ft_draw_line(p1, p2, vars);
			y++;
		}
		x++;
	}
} */
