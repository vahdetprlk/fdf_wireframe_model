/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:53:27 by vparlak           #+#    #+#             */
/*   Updated: 2023/08/24 20:48:28 by vparlak          ###   ########.fr       */
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
	x = point_1.x;
	while (x <= point_2.x - 1 && x++)
	{
		if (is_steep)
		{
			if (rfpart(intery) != 0)
				draw_pixel(ipart(intery), x, rfpart(intery), m);
			if (fpart(intery) != 0)
				draw_pixel(ipart(intery) + 1, x, fpart(intery), m);
		}
		else
		{
			if (rfpart(intery) != 0)
				draw_pixel(x, ipart(intery), rfpart(intery), m);
			if (fpart(intery) != 0)
				draw_pixel(x, ipart(intery) + 1, fpart(intery), m);
		}
		intery += gradient;
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

void	ft_bzero(void *s, int n)
{
	int	i;
	char	*ptr;

	i = 0;
	ptr = s;
	while (i < n)
		ptr[i++] = '\0';
}

int main(void)
{
    void *mlx_ptr;
    void *win_ptr;
	void *img_ptr;
	char *data_addr;
	int bpp;
	int size_line;
	int endian;

    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, 800, 800, "My Window");
	img_ptr = mlx_new_image(mlx_ptr, 30, 30);
	data_addr = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
	ft_bzero(data_addr, 800 * 800 * (bpp / 8));
	int		i;
		i = (1) + (1);
		data_addr[i] = 0xFF;
		data_addr[++i] = 0xFF >> 8;
		data_addr[++i] = 0xFF >> 16;
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 50, 50);

	mlx_loop(mlx_ptr);
}
