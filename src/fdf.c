/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:53:27 by vparlak           #+#    #+#             */
/*   Updated: 2023/09/20 15:51:59 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <unistd.h>
#include <stdio.h>
#include <math.h>

void	ft_calculate_offset(t_vars	*vars)
{
	int	x;
	int	y;
	float x_offset;
	float y_offset;

	y = vars->map.axis;
	x = vars->map.axis;

	x_offset = WIDTH * 0.8;
	x_offset = x_offset / vars->map.axis;
	y_offset = HEIGHT * 0.8;
	y_offset = y_offset / vars->map.ordinate;
	if (y_offset > x_offset)
		vars->offset = x_offset;
	vars->offset = y_offset;
}

int	main(int argc, char **argv)
{
	t_vars	*vars;

	if (argc == 2)
	{
		vars = &(t_vars){0};
		ft_check_map(argv[1], vars);
		ft_vars_init(vars);
		ft_calculate_offset(vars);
		ft_draw(vars);
		mlx_put_image_to_window(vars->m.mlx, vars->m.win, vars->img_ptr, 0, 0);
		ft_hooks(vars);
		mlx_loop(vars->m.mlx);
	}
	else
		write(2, "Usage: ./fdf <filename>\n", 24);
	return (0);
}
