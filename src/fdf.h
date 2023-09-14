/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:48:47 by vparlak           #+#    #+#             */
/*   Updated: 2023/09/15 01:14:24 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIDTH 1920
# define HEIGHT 1080
# include <string.h>


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
	int		**map;
	int 	axis;
	int		ordinate;
}	t_vars;

char		**ft_split(char const *s, char c);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
void		*ft_memcpy(void *dst, const void *src, size_t n);
char		**ft_free_tab(char **tab);
void		**ft_free_map(t_vars *vars);

#endif
