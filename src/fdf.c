/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:53:27 by vparlak           #+#    #+#             */
/*   Updated: 2023/09/18 22:19:30 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <unistd.h>
#include <stdio.h>

int	handle_loop(void *params)
{
	t_vars	*vars;

	vars = params;
	mlx_clear_window(vars->m.mlx, vars->m.win);

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
		(void)argv;
	//	ft_check_map(argv[1], vars);
		ft_vars_init(vars);
		ft_hooks(vars);
		mlx_loop_hook(vars->m.mlx, handle_loop, vars);
		mlx_loop(vars->m.mlx);
	}
	write(2, "Usage: ./fdf <filename>\n", 24);
	return (0);
}

