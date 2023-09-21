/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_projection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 23:03:24 by vparlak           #+#    #+#             */
/*   Updated: 2023/09/21 23:23:11 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static t_point	ft_rotation_2d(t_point p1, t_point origin, int teta)
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

static void	ft_rotation_origin(t_vars *vars)
{
	t_point			point;
	int				x;
	int				y;

	x = 0;
	while (x < vars->map.axis)
	{
		y = 0;
		while (y < vars->map.ordinate)
		{
			point.x = vars->r_map[x][y].x;
			point.y = vars->r_map[x][y].y;
			point = ft_rotation_2d(point, vars->origin, vars->angle);
			vars->r_map[x][y].x = point.x;
			vars->r_map[x][y].y = point.y;
			y++;
		}
		x++;
	}
}

void	ft_projection(t_vars *vars)
{
	t_point			point;
	int				x;
	int				y;

	ft_rotation_origin(vars);
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
			point = ft_rotation_2d(point, vars->origin,
					(180 - (90 + vars->angle)) - vars->angle);
			vars->r_map[x][y].x = point.x;
			vars->r_map[x][y].y = point.y - vars->r_map[x][y].z;
			y++;
		}
		x++;
	}
}
