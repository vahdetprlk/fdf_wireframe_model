/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:53:27 by vparlak           #+#    #+#             */
/*   Updated: 2023/09/21 17:26:27 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <unistd.h>
#include <math.h>

void	ft_clear_win(t_vars *vars)
{
	int	j;

	j = WIDTH * HEIGHT * 4;
	ft_bzero(vars->data_addr, j);
}

void	ft_calculate_offset(t_vars	*vars)
{
	int		x;
	int		y;
	float	x_offset;
	float	y_offset;

	int min_z = 0;
	int max_z = 0;
	x = 0;
	while (x < vars->map.axis)
	{
		y = 0;
		while (y < vars->map.ordinate)
		{
			if (min_z > vars->map.points[x][y].z)
				min_z = vars->map.points[x][y].z;
			if (max_z < vars->map.points[x][y].z)
				max_z = vars->map.points[x][y].z;
			y++;
		}
		x++;
	}
	x_offset = WIDTH * 0.8;
	x_offset = x_offset / (vars->map.axis + vars->map.ordinate)/*  * cos(30 * M_PI / 180) */;
	y_offset = HEIGHT * 0.8;
	y_offset = y_offset / (vars->map.axis + vars->map.ordinate)/*  * sin(30 * M_PI / 180) */;
	if (HEIGHT / y_offset > WIDTH / x_offset)
	{
		vars->x_offset = x_offset;
		vars->y_offset = x_offset * tan(30 * M_PI / 180);
		vars->offset = y_offset / sin(30 * M_PI / 180);
	}
	else
	{
		vars->x_offset = y_offset / tan(30 * M_PI / 180);
		vars->y_offset = y_offset;
		vars->offset = y_offset / sin(30 * M_PI / 180);
	}
	vars->i = 0;
}

int	ft_loop_mlx(t_vars *vars)
{
	ft_clear_win(vars);
	ft_draw(vars);
	mlx_put_image_to_window(vars->m.mlx, vars->m.win, vars->img_ptr, 0, 0);
	return (0);
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
		mlx_loop_hook(vars->m.mlx, ft_loop_mlx, vars);
		ft_hooks(vars);
		mlx_loop(vars->m.mlx);
	}
	else
		write(2, "Usage: ./fdf <filename>\n", 24);
	return (0);
}
