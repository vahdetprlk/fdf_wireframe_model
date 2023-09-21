/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 17:05:37 by vparlak           #+#    #+#             */
/*   Updated: 2023/09/22 02:00:32 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_set_r_map(t_vars *vars)
{
	int		x;
	int		y;

	x = 0;
	while (x < vars->map.axis)
	{
		y = 0;
		while (y < vars->map.ordinate)
		{
			vars->r_map[x][y].x = (x * vars->offset) + vars->origin.x;
			vars->r_map[x][y].y = (y * vars->offset) + vars->origin.y;
			vars->r_map[x][y].z = (vars->map.points[x][y].z * vars->z_offset);
			y++;
		}
		x++;
	}
}

static void	ft_draw_ordinate(t_vars *vars)
{
	t_point	p1;
	t_point	p2;
	int		x;
	int		y;

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
}

static void	ft_draw_axis(t_vars *vars)
{
	t_point	p1;
	t_point	p2;
	int		x;
	int		y;

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

void	ft_draw(t_vars *vars)
{
	if (vars->projection == 0)
	{
		vars->origin.x = ((WIDTH - ((vars->map.axis + vars->map.ordinate)
						* vars->x_offset)) / 2)
			+ (vars->x_offset * vars->map.ordinate);
		vars->origin.y = ((HEIGHT - ((vars->map.axis + vars->map.ordinate)
						* vars->y_offset)) / 2) + (vars->y_offset);
	}
	else
	{
		vars->origin.x = ((WIDTH - (vars->offset
						* (vars->map.axis))) + vars->offset) / 2;
		vars->origin.y = ((HEIGHT - (vars->offset
						* (vars->map.ordinate))) + vars->offset) / 2;
	}
	vars->origin.x += vars->i;
	vars->origin.y += vars->j;
	ft_set_r_map(vars);
	if (vars->projection == 0)
		ft_projection_iso(vars);
	// else
	// 	ft_projection_conic(vars);
	ft_draw_axis(vars);
	ft_draw_ordinate(vars);
}
