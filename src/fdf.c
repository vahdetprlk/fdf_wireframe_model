/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:18:05 by vparlak           #+#    #+#             */
/*   Updated: 2023/07/09 21:46:15 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	int		i;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 532, 532, "title");
	img_ptr = mlx_new_image(mlx_ptr, 300, 300);
	i = 0;
	while (500 > i)
	{
		
		i++;
	}

	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
	mlx_loop(mlx_ptr);
}

