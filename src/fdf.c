/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 20:12:30 by vparlak           #+#    #+#             */
/*   Updated: 2023/08/06 21:17:37 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

void	put_line(t_window window, t_point p_a, t_point p_b, int color)
{
	int	i;
	int	j;
	int	k;

	if (p_a.y == p_b.y)
	{
		if (p_a.x < p_b.x)
		{
			i = p_a.x;
			while (i <= p_b.x)
			{
				mlx_pixel_put(window.mlx, window.win, i, p_a.y, color);
				i++;
			}
		}
		else if (p_a.x > p_b.x)
		{
			i = p_b.x;
			while (i <= p_a.x)
			{
				mlx_pixel_put(window.mlx, window.win, i, p_a.y, color);
				i++;
			}
		}
	}
	else if (p_a.x == p_b.x)
	{
		if (p_a.y < p_b.y)
		{
			i = p_a.y;
			while (i <= p_b.y)
			{
				mlx_pixel_put(window.mlx, window.win, p_a.x, i, color);
				i++;
			}
		}
		else if (p_a.y > p_b.y)
		{
			i = p_b.y;
			while (i <= p_a.y)
			{
				mlx_pixel_put(window.mlx, window.win, p_a.x, i, color);
				i++;
			}
		}
	}
	else
	{
		j = 0;
		i = 0;
		while (i < 100)
		{
			mlx_pixel_put(window.mlx, window.win, i, j - 4, 0xAAFFFFFF);
			mlx_pixel_put(window.mlx, window.win, i, j - 3, 0x88FFFFFF);
			mlx_pixel_put(window.mlx, window.win, i, j - 2, 0x55FFFFFF);
			mlx_pixel_put(window.mlx, window.win, i, j - 1, 0x33FFFFFF);
			k = 0;
			while (k < 1)
			{
				mlx_pixel_put(window.mlx, window.win, i, j, 0x00FFFFFF);
				j++;
				k++;
			}
			mlx_pixel_put(window.mlx, window.win, i, j, 0x33FFFFFF);
			mlx_pixel_put(window.mlx, window.win, i, j + 1, 0x55FFFFFF);
			mlx_pixel_put(window.mlx, window.win, i, j + 2, 0x88FFFFFF);
			mlx_pixel_put(window.mlx, window.win, i, j + 3, 0xAAFFFFFF);
			i++;
		}
	}
}

int	main(void)
{
	t_window	window;
	t_point		point_a;
	t_point		point_b;
	t_point		point_c;
	t_point		point_d;

	window.mlx = mlx_init();
	window.win = mlx_new_window(window.mlx, 500, 500, "Test");
	point_a.x = 10;
	point_a.y = 20;
	point_b.x = 20;
	point_b.y = 20;
	point_c.x = 30;
	point_c.y = 20;
	point_d.x = 31;
	point_d.y = 10;
	put_line(window, point_a, point_b, 0xF0FFFFFF);
	put_line(window, point_b, point_c, 0xE0FFFFFF);
	put_line(window, point_d, point_c, 0xA0FFFFFF);
	mlx_loop(window.mlx);
}
