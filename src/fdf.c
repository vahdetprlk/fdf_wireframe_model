/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:53:27 by vparlak           #+#    #+#             */
/*   Updated: 2023/08/25 17:40:17 by vparlak          ###   ########.fr       */
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

void	draw_pixel_smooth(int x, int y, float brightness, t_vars *vars)
{
	int	offset;
	int	color;

	color = brightness * 0xFF;
    offset = y * *(vars->size_line) + x * (*(vars->bpp) / 8);
	vars->data_addr[offset] = color;
    vars->data_addr[offset + 1] = color;
    vars->data_addr[offset + 2] = color;
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

void	draw_loop_smooth(t_point point_1, t_point point_2, int is_steep, t_vars *vars)
{
	int		x;
	float	gradient;
	float	intery;

	gradient = (float)(point_2.y - point_1.y) / (point_2.x - point_1.x);
	intery = point_1.y + gradient;
	x = point_1.x + 1;
	while (x <= point_2.x)
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

void	ft_bzero(void *s, int n)
{
	int	i;
	char	*ptr;

	i = 0;
	ptr = s;
	while (i < n)
		ptr[i++] = '\0';
}

int main()
{
	t_vars vars;
	t_point point_1;
	t_point point_2;
	t_point point_3;
	t_point point_4;
	int bpp;
	int size_line;
	int endian;

    vars.m.mlx = mlx_init();
    vars.m.win = mlx_new_window(vars.m.mlx, 800, 800, "My Window");
    vars.img_ptr = mlx_new_image(vars.m.mlx, 800, 800);
	vars.data_addr = mlx_get_data_addr(vars.img_ptr, &bpp, &size_line, &endian);
	vars.bpp = &bpp;
	vars.size_line = &size_line;
	vars.endian = &endian;
	point_1.x = 1;
	point_1.y = 10;
	point_2.x = 100;
	point_2.y = 100;
	point_3.x = 100;
	point_3.y = 50;
	point_4.x = 150;
	point_4.y = 200;
	draw_line_smooth(point_1, point_2, &vars);
	draw_line_smooth(point_3, point_4, &vars);
	mlx_put_image_to_window(vars.m.mlx, vars.m.win, vars.img_ptr, 0, 0);
    mlx_loop(vars.m.mlx);
    return 0;
}

