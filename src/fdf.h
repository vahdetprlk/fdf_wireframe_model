/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:48:47 by vparlak           #+#    #+#             */
/*   Updated: 2023/08/28 14:34:51 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}	t_mlx;

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	float	brightness;
}	t_point;

typedef struct s_vars
{
	t_mlx	m;
	char	*data_addr;
	int		size_line;
	int		bpp;
	int		endian;
	void	*img_ptr;
}	t_vars;

#endif
