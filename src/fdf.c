/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:53:27 by vparlak           #+#    #+#             */
/*   Updated: 2023/09/20 19:28:38 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <unistd.h>
#include <stdio.h>
#include <math.h>

void	ft_calculate_offset(t_vars	*vars)
{
	int		x;
	int		y;
	float	x_offset;
	float	y_offset;
	float	z_offset;

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
	z_offset = HEIGHT * 0.8;
	z_offset = 
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
