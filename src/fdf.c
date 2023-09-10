/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:53:27 by vparlak           #+#    #+#             */
/*   Updated: 2023/09/10 18:50:38 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "ft_printf.h"
#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const char	*s;
	char		*d;

	d = (char *)dst;
	s = (const char *)src;
	if (!d && !s)
		return (NULL);
	while (n--)
		*d++ = *s++;
	return (dst);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len_src;
	size_t	len;

	len_src = ft_strlen(src);
	if (dstsize)
	{
		if (len_src >= dstsize)
			len = dstsize - 1;
		else
			len = len_src;
		ft_memcpy(dst, src, len);
		dst[len] = '\0';
	}
	return (len_src);
}

static char	**ft_malloc_error(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static size_t	ft_nb_words(char const *s, char c)
{
	size_t	i;
	size_t	nb_words;

	if (!s[0])
		return (0);
	i = 0;
	nb_words = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			nb_words++;
			while (s[i] && s[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (s[i - 1] != c)
		nb_words++;
	return (nb_words);
}

static void	ft_get_next_word(char **next_word, size_t *next_word_len, char c)
{
	size_t	i;

	*next_word += *next_word_len;
	*next_word_len = 0;
	i = 0;
	while (**next_word && **next_word == c)
		(*next_word)++;
	while ((*next_word)[i])
	{
		if ((*next_word)[i] == c)
			return ;
		(*next_word_len)++;
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	char	*next_word;
	size_t	next_word_len;
	size_t	i;

	if (!s)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (ft_nb_words(s, c) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	next_word = (char *)s;
	next_word_len = 0;
	while (i < ft_nb_words(s, c))
	{
		ft_get_next_word(&next_word, &next_word_len, c);
		tab[i] = (char *)malloc(sizeof(char) * (next_word_len + 1));
		if (!tab[i])
			return (ft_malloc_error(tab));
		ft_strlcpy(tab[i], next_word, next_word_len + 1);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

int	ft_abs(int x)
{
	if (x < 0)
		x = -x;
	return (x);
}

float	ft_fpart(float x)
{
	return (x - floor(x));
}

float	ft_rfpart(float x)
{
	return (1.0 - ft_fpart(x));
}

int	ft_ipart(float x)
{
	return ((int)x);
}

void	ft_draw_pixel(int x, int y, float brightness, t_vars *vars)
{
	int	offset;

	offset = y * (vars->size_line) + x * ((vars->bpp) / 8);
	vars->data_addr[offset] = 0x00 * brightness;
	vars->data_addr[offset + 1] = 0x7F * brightness;
	vars->data_addr[offset + 2] = 0xFF * brightness;
}

int	ft_swap_origins(t_point *point_1, t_point *point_2)
{
	int	is_steep;
	int	temp;

	is_steep = ft_abs(point_2->y - point_1->y)
		> ft_abs(point_2->x - point_1->x);
	if (is_steep)
	{
		temp = point_1->x;
		point_1->x = point_1->y;
		point_1->y = temp;
		temp = point_2->x;
		point_2->x = point_2->y;
		point_2->y = temp;
	}
	if (point_1->x > point_2->x)
	{
		temp = point_1->x;
		point_1->x = point_2->x;
		point_2->x = temp;
		temp = point_1->y;
		point_1->y = point_2->y;
		point_2->y = temp;
	}
	return (is_steep);
}

void	ft_draw_pixel_loop(int is_steep, float intery, int x, t_vars *vars)
{
	if (is_steep)
	{
		if (ft_rfpart(intery) != 0)
			ft_draw_pixel(ft_ipart(intery), x, ft_rfpart(intery), vars);
		if (ft_fpart(intery) != 0)
			ft_draw_pixel(ft_ipart(intery) + 1, x, ft_fpart(intery), vars);
	}
	else
	{
		if (ft_rfpart(intery) != 0)
			ft_draw_pixel(x, ft_ipart(intery), ft_rfpart(intery), vars);
		if (ft_fpart(intery) != 0)
			ft_draw_pixel(x, ft_ipart(intery) + 1, ft_fpart(intery), vars);
	}
}

void	ft_draw_loop(t_point p1, t_point p2, int is_steep, t_vars *vars)
{
	int		x;
	float	gradient;
	float	intery;

	gradient = (float)(p2.y - p1.y) / (p2.x - p1.x);
	intery = p1.y + gradient;
	x = p1.x + 1;
	while (x <= p2.x)
	{
		ft_draw_pixel_loop(is_steep, intery, x, vars);
		intery += gradient;
		x++;
	}
}

void ft_draw_line(t_point point_1, t_point point_2, t_vars *vars)
{
	int		is_steep;

	is_steep = ft_swap_origins(&point_1, &point_2);
	point_1.brightness = 1;
	point_2.brightness = 1;
	if (is_steep)
		ft_draw_pixel(point_1.y, point_1.x, 1, vars);
	else
		ft_draw_pixel(point_1.x, point_1.y, 1, vars);
	if (is_steep)
		ft_draw_pixel(point_2.y, point_2.x, 1, vars);
	else
		ft_draw_pixel(point_2.x, point_2.y, 1, vars);
	ft_draw_loop(point_1, point_2, is_steep, vars);
}

int	ft_close_x(t_vars *vars)
{
	mlx_destroy_image(vars->m.mlx, vars->img_ptr);
	mlx_destroy_window(vars->m.mlx, vars->m.win);
	exit(0);
	return (1);
}

int	ft_close(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_image(vars->m.mlx, vars->img_ptr);
		mlx_destroy_window(vars->m.mlx, vars->m.win);
		exit(0);
	}
	return (1);
}

void ft_vars_init(t_vars	*vars)
{
	vars->m.mlx = mlx_init();
	if (!vars->m.mlx)
		exit(EXIT_FAILURE);
	vars->m.win = mlx_new_window(vars->m.mlx, 900, 900, "My Window");
	if (!vars->m.win)
		exit(EXIT_FAILURE);
	vars->img_ptr = mlx_new_image(vars->m.mlx, 900, 900);
	if (!vars->img_ptr)
	{
		mlx_destroy_window(vars->m.mlx, vars->m.win);
		exit(EXIT_FAILURE);
	}
	vars->data_addr = mlx_get_data_addr(vars->img_ptr,
			&vars->bpp, &vars->size_line, &vars->endian);
	if (!vars->data_addr)
	{
		mlx_destroy_image(vars->m.mlx, vars->img_ptr);
		mlx_destroy_window(vars->m.mlx, vars->m.win);
		exit(EXIT_FAILURE);
	}
}

void	ft_draw(t_vars *vars)
{
	t_point point_1;
	t_point point_2;

	point_1.x = 20;
	point_1.y = 10;
	point_2.x = 300;
	point_2.y = 450;
	ft_draw_line(point_1, point_2, vars);
}

void	ft_hooks(t_vars *vars)
{
	mlx_hook(vars->m.win, 2, 1L << 2, ft_close, vars);
	mlx_hook(vars->m.win, 17, 1L << 17, ft_close_x, vars);
}

void	ft_str_to_points(char **points_str, int line_index)
{
	//burada points
	(void)points_str;
	(void)line_index;
}


void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_read_map(char **argv)
{
	int		fd;
	int 	i;
	char	*line;
	char	**points_str;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_printf("open error: No such file or directory\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	line = get_next_line(fd);
	if(!line)
		exit(EXIT_FAILURE);
	while  (line != NULL)
	{
		ft_printf("%s", line);
		points_str = ft_split(line, ' ');
		if (!points_str)
		{
			ft_free_tab(points_str);
			free(line);
			exit(EXIT_FAILURE);
		}
		ft_str_to_points(points_str, i);
		ft_free_tab(points_str);
		free(line);
		line = get_next_line(fd);
		if(!line)
			exit(EXIT_FAILURE);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_vars	*vars;


	if (argc == 2)
	{
		ft_read_map(argv);
		vars = &(t_vars){0};
		ft_vars_init(vars);
		ft_draw(vars);
		mlx_put_image_to_window(vars->m.mlx, vars->m.win, vars->img_ptr, 0, 0);
		ft_hooks(vars);
		mlx_loop(vars->m.mlx);
	}
	ft_printf("Usage: ./fdf <filename>\n");
	return (0);

}
