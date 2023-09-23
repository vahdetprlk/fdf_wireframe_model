/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:47:14 by vparlak           #+#    #+#             */
/*   Updated: 2023/09/23 03:37:07 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static int	ft_swap_origins(t_vars *vars)
{
	int	is_steep;
	int	temp;

	is_steep = ft_abs(vars->p2.y - vars->p1.y)
		> ft_abs(vars->p2.x - vars->p1.x);
	if (is_steep)
	{
		temp = vars->p1.x;
		vars->p1.x = vars->p1.y;
		vars->p1.y = temp;
		temp = vars->p2.x;
		vars->p2.x = vars->p2.y;
		vars->p2.y = temp;
	}
	if (vars->p1.x > vars->p2.x)
	{
		temp = vars->p1.x;
		vars->p1.x = vars->p2.x;
		vars->p2.x = temp;
		temp = vars->p1.y;
		vars->p1.y = vars->p2.y;
		vars->p2.y = temp;
	}
	return (is_steep);
}

static void	ft_draw_pixel(int x, int y, float brightness, t_vars *vars)
{
	int	offset;
	int	color;

	color = vars->render_color;
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		offset = y * (vars->size_line) + x * ((vars->bpp) / 8);
		if (vars->data_addr[offset] < 127
			&& vars->data_addr[offset + 1] < 127
			&& vars->data_addr[offset + 2] < 127)
		{
			vars->data_addr[offset] = (color & 0xFF) * brightness;
			vars->data_addr[offset + 1] = ((color >> 8) & 0xFF) * brightness;
			vars->data_addr[offset + 2] = ((color >> 16) & 0xFF) * brightness;
		}
	}
}

static void	ft_draw_pixel_loop(int is_steep, float intery, int x, t_vars *vars)
{
	if (is_steep)
	{
		if (ft_rfpart(intery) != 0)
			ft_draw_pixel(ft_ipart(intery), x, ft_rfpart(intery), vars);
		if (ft_fpart(intery) != 0)
			ft_draw_pixel(ft_ipart(intery) + 1, x, ft_fpart(intery), vars);
	}
	else
	{
		if (ft_rfpart(intery) != 0)
			ft_draw_pixel(x, ft_ipart(intery), ft_rfpart(intery), vars);
		if (ft_fpart(intery) != 0)
			ft_draw_pixel(x, ft_ipart(intery) + 1, ft_fpart(intery), vars);
	}
}

static void	ft_draw_loop(int is_steep, t_vars *vars)
{
	int		x;
	float	gradient;
	float	intery;

	gradient = (float)(vars->p2.y - vars->p1.y) / (vars->p2.x - vars->p1.x);
	intery = vars->p1.y + gradient;
	x = vars->p1.x + 1;
	while (x <= vars->p2.x)
	{
		ft_draw_pixel_loop(is_steep, intery, x, vars);
		intery += gradient;
		x++;
	}
}

void	ft_draw_line(t_vars *vars)
{
	int		is_steep;

	if (vars->p1.color == 0)
		vars->p1.color = 0xFF7F00;
	vars->render_color = vars->p1.color;
	is_steep = ft_swap_origins(vars);
	if (is_steep)
		ft_draw_pixel(vars->p1.y, vars->p1.x, 1, vars);
	else
		ft_draw_pixel(vars->p1.x, vars->p1.y, 1, vars);
	if (vars->p2.color == 0)
		vars->p2.color = 0xFF7F00;
	vars->render_color = vars->p2.color;
	if (is_steep)
		ft_draw_pixel(vars->p2.y, vars->p2.x, 1, vars);
	else
		ft_draw_pixel(vars->p2.x, vars->p2.y, 1, vars);
	ft_draw_loop(is_steep, vars);
}
