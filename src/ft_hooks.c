/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 22:22:32 by vparlak           #+#    #+#             */
/*   Updated: 2023/09/22 04:14:12 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <stdlib.h>

static int	ft_close_x(t_vars *vars)
{
	ft_free_map_point(vars);
	ft_free_r_map(vars);
	mlx_destroy_image(vars->m.mlx, vars->img_ptr);
	mlx_destroy_window(vars->m.mlx, vars->m.win);
	exit(EXIT_SUCCESS);
	return (1);
}

static void	ft_key_press_cont(int keycode, t_vars *vars)
{
	if (keycode == 6)
	{
		if (vars->projection == 0)
			vars->projection = 1;
		else if (vars->projection == 1)
			vars->projection = 0;
	}
	if (keycode == 38)
		if (vars->angle <= 47)
			vars->angle++;
	if (keycode == 40)
		if (vars->angle >= 10)
			vars->angle--;
}

static int	ft_key_press(int keycode, t_vars *vars)
{
	if (keycode == 53)
		ft_close_x(vars);
	if (keycode == 0)
		vars->offset++;
	if (keycode == 1)
		if (vars->offset > 2)
			vars->offset--;
	if (keycode == 2)
		vars->i += 4;
	if (keycode == 3)
		vars->i -= 4;
	if (keycode == 4)
		vars->j += 4;
	if (keycode == 5)
		vars->j -= 4;
	ft_key_press_cont(keycode, vars);
	return (1);
}

void	ft_hooks(t_vars *vars)
{
	mlx_hook(vars->m.win, 2, 1L << 2, ft_key_press, vars);
	mlx_hook(vars->m.win, 17, 1L << 17, ft_close_x, vars);
}
