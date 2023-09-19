/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:53:27 by vparlak           #+#    #+#             */
/*   Updated: 2023/09/19 20:26:32 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <unistd.h>
#include <stdio.h>

void	ft_calculate_offset(t_vars	*vars)
{
	float width_offset = (WIDTH * 0.8) / vars->map.axis;
	float height_offset = (HEIGHT * 0.8) / vars->map.ordinate;
	float width_border = WIDTH * 0.1;
	float height_border = HEIGHT * 0.1;
	if (width_offset <= height_offset)
	{
		printf("Soldan, Sağdan: %f\n", width_border);
		printf("Ofset: %f", width_offset);
		vars->offset = width_offset;
	}
	else
	{
		printf("Alttan, Üstten: %f\n", height_border);
		printf("Ofset: %f", height_offset);
		vars->offset = height_offset;
	}
	if (vars->offset > 100)
		vars->offset = 100;
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
