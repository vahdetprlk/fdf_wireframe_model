/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:53:27 by vparlak           #+#    #+#             */
/*   Updated: 2023/08/26 19:25:38 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <stdlib.h>
#include <math.h>

#include <stdio.h>

#define WIDTH 1920
#define HEIGHT 1080

int	ft_abs(int x)
{
	if (x < 0)
		x = -x;
	return (x);
}

float	fpart(float x)
{
	return (x - floor(x));
}

float	rfpart(float x)
{
	return (1.0 - fpart(x));
}

int	ipart(float x)
{
	return ((int)x);
}

void	draw_pixel_smooth(int x, int y, float brightness, t_vars *vars)
{
	int	offset;

	offset = y * *(vars->size_line) + x * (*(vars->bpp) / 8);
	vars->data_addr[offset] = 0x00 * brightness;
	vars->data_addr[offset + 1] = 0x7F * brightness;
	vars->data_addr[offset + 2] = 0xFF * brightness;
	//vars->data_addr[offset + 3] = 0xFF * (1 - brightness);~
}

int	swap_origins(t_point *point_1, t_point *point_2)
{
	int	is_steep;
	int	temp;

	is_steep = ft_abs(point_2->y - point_1->y)
		> ft_abs(point_2->x - point_1->x);
	if (is_steep)
	{
		temp = point_1->x;
		point_1->x = point_1->y;
		point_1->y = temp;
		temp = point_2->x;
		point_2->x = point_2->y;
		point_2->y = temp;
	}
	if (point_1->x > point_2->x)
	{
		temp = point_1->x;
		point_1->x = point_2->x;
		point_2->x = temp;
		temp = point_1->y;
		point_1->y = point_2->y;
		point_2->y = temp;
	}
	return (is_steep);
}

void	draw_loop(int is_steep, float intery, int x, t_vars *vars)
{
	if (is_steep)
	{
		if (rfpart(intery) != 0)
			draw_pixel_smooth(ipart(intery), x, rfpart(intery), vars);
		if (fpart(intery) != 0)
			draw_pixel_smooth(ipart(intery) + 1, x, fpart(intery), vars);
	}
	else
	{
		if (rfpart(intery) != 0)
			draw_pixel_smooth(x, ipart(intery), rfpart(intery), vars);
		if (fpart(intery) != 0)
			draw_pixel_smooth(x, ipart(intery) + 1, fpart(intery), vars);
	}
}

void	draw_loop_smooth(t_point p1, t_point p2, int is_steep, t_vars *vars)
{
	int		x;
	float	gradient;
	float	intery;

	gradient = (float)(p2.y - p1.y) / (p2.x - p1.x);
	intery = p1.y + gradient;
	x = p1.x + 1;
	while (x <= p2.x)
	{
		draw_loop(is_steep, intery, x, vars);
		intery += gradient;
		x++;
	}
}

void draw_line_smooth(t_point point_1, t_point point_2, t_vars *vars)
{
	int		is_steep;

	is_steep = swap_origins(&point_1, &point_2);
	point_1.brightness = 1;
	point_2.brightness = 1;
	if (is_steep)
		draw_pixel_smooth(point_1.y, point_1.x, 1, vars);
	else
		draw_pixel_smooth(point_1.x, point_1.y, 1, vars);
	if (is_steep)
		draw_pixel_smooth(point_2.y, point_2.x, 1, vars);
	else
		draw_pixel_smooth(point_2.x, point_2.y, 1, vars);
	draw_loop_smooth(point_1, point_2, is_steep, vars);
}

void	safe_exit(int status)
{
	exit(status);
}

void test()
{
  char* pTmp = (char*)malloc(sizeof(char)*1);
  (void) pTmp;
}

int main()
{
	t_vars vars;
	t_point point_1;
	t_point point_2;
	t_point point_3;
	t_point point_4;
	t_point point_5;
	t_point point_6;

	int bpp;
	int size_line;
	int endian;

    vars.m.mlx = mlx_init();
	if (!vars.m.mlx)
		safe_exit(EXIT_FAILURE);
    vars.m.win = mlx_new_window(vars.m.mlx, 800, 800, "My Window");
	if (!vars.m.win)
		safe_exit(EXIT_FAILURE);
    vars.img_ptr = mlx_new_image(vars.m.mlx, 800, 800);
	if (!vars.img_ptr)
		safe_exit(EXIT_FAILURE);
	vars.data_addr = mlx_get_data_addr(vars.img_ptr, &bpp, &size_line, &endian);
	if (!vars.data_addr)
		safe_exit(EXIT_FAILURE);
	vars.bpp = &bpp;
	vars.size_line = &size_line;
	vars.endian = &endian;
	point_1.x = 0;
	point_1.y = 0;
	point_2.x = 300;
	point_2.y = 799;
	point_3.x = 0;
	point_3.y = 50;
	point_4.x = 150;
	point_4.y = 200;
	point_5.x = 500;
	point_5.y = 500;
	point_6.x = 500;
	point_6.y = 500;
	draw_line_smooth(point_1, point_2, &vars);
	draw_line_smooth(point_3, point_4, &vars);
	draw_line_smooth(point_5, point_6, &vars);
	mlx_put_image_to_window(vars.m.mlx, vars.m.win, vars.img_ptr, 0, 0);
    mlx_loop(vars.m.mlx);
    return 0;
}

