/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:48:47 by vparlak           #+#    #+#             */
/*   Updated: 2023/08/02 18:01:42 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

typedef struct s_mlx_window
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_mlx_window;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

#endif
