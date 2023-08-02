/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 20:12:30 by vparlak           #+#    #+#             */
/*   Updated: 2023/08/02 18:16:49 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

void	put_line(t_mlx_window mlx_window, t_point p_a, t_point p_b, int color)
{
	mlx_pixel_put(mlx_window.mlx_ptr, mlx_window.win_ptr, p_a.x, p_a.y, color);
	mlx_pixel_put(mlx_window.mlx_ptr, mlx_window.win_ptr, p_b.x, p_b.y, color);
}

int	main(void)
{
	t_mlx_window	mlx_window;
	t_point			point_a;
	t_point			point_b;

	mlx_window.mlx_ptr = mlx_init();
	mlx_window.win_ptr = mlx_new_window(mlx_window.mlx_ptr, 500, 500, "Test");
	point_a.x = 20;
	point_a.y = 20;
	point_b.x = 40;
	point_b.y = 20;
	put_line(mlx_window, point_a, point_b, 0x00FFFFFF);
	mlx_loop(mlx_window.mlx_ptr);
}
