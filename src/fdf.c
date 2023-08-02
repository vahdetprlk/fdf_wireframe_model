/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 20:12:30 by vparlak           #+#    #+#             */
/*   Updated: 2023/08/02 18:03:50 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

void	put_line(t_mlx_window mlx_window, t_point p, int color)
{
	mlx_pixel_put(mlx_window.mlx_ptr, mlx_window.win_ptr, p.x, p.y, color);
}

int	main(void)
{
	t_mlx_window	mlx_window;
	t_point			point;

	mlx_window.mlx_ptr = mlx_init();
	mlx_window.win_ptr = mlx_new_window(mlx_window.mlx_ptr, 500, 500, "Test");
	point.x = 20;
	point.y = 20;
	put_line(mlx_window, point, 0x00FFFFFF);
	mlx_hook()
	mlx_loop(mlx_window.mlx_ptr);
}
