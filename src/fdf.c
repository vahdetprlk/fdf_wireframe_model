/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:53:27 by vparlak           #+#    #+#             */
/*   Updated: 2023/08/23 20:40:04 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <math.h>

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

void	draw_pixel(int x, int y, float brightness, t_mlx m)
{
	int	color;
	int	pixel_color;

	color = (int)(brightness * 0xFF);
	pixel_color = (color << 16) | (color << 8) | color;
	mlx_pixel_put(m.mlx, m.win, x, y, pixel_color);
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

void	draw_loop(t_point point_1, t_point point_2, int is_steep, t_mlx m)
{
	int		x;
	float	gradient;
	float	intery;

	gradient = (float)(point_2.y - point_1.y) / (point_2.x - point_1.x);
	intery = point_1.y + gradient;
	if (is_steep)
	{
		x = point_1.x + 1;
		while (x <= point_2.x - 1)
		{
			if (rfpart(intery) != 0)
				draw_pixel(ipart(intery), x, rfpart(intery), m);
			if (fpart(intery) != 0)
				draw_pixel(ipart(intery) + 1, x, fpart(intery), m);
			intery += gradient;
			x++;
		}
	}
	else
	{
		x = point_1.x + 1;
		while (x <= point_2.x - 1)
		{
			if (rfpart(intery) != 0)
				draw_pixel(x, ipart(intery), rfpart(intery), m);
			if (fpart(intery) != 0)
				draw_pixel(x, ipart(intery) + 1, fpart(intery), m);
			intery += gradient;
			x++;
		}
	}
}

void draw_line(t_point point_1, t_point point_2, t_mlx mlx_n)
{
	int		is_steep;

	is_steep = swap_origins(&point_1, &point_2);
	point_1.brightness = 1;
	point_2.brightness = 1;
	if (is_steep)
		draw_pixel(point_1.y, point_1.x, 1, mlx_n);
	else
		draw_pixel(point_1.x, point_1.y, 1, mlx_n);
	if (is_steep)
		draw_pixel(point_2.y, point_2.x, 1, mlx_n);
	else
		draw_pixel(point_2.x, point_2.y, 1, mlx_n);
	draw_loop(point_1, point_2, is_steep, mlx_n);
}

int main()
{
	t_mlx	mlx;
	t_point	point_1;
	t_point	point_2;

	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "Wu Line Drawing Example");
	point_1.x = 200;
	point_1.y = 2000;
	point_2.x = 1000;
	point_2.y = 250;


	draw_line(point_1, point_2, mlx);




	mlx_loop(mlx.mlx);
	return (0);
}
