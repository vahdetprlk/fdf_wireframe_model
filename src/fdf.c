/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:18:05 by vparlak           #+#    #+#             */
/*   Updated: 2023/07/08 18:21:16 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "title");

	mlx_string_put(mlx_ptr, win_ptr, 250, 250, 0x00FFFFFF, "Hello World!");
	mlx_string_put(mlx_ptr, win_ptr, 250, 300, 0x00FFFFFF, "Hello World!");



	mlx_loop(mlx_ptr);

}
