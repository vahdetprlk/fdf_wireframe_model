/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:53:27 by vparlak           #+#    #+#             */
/*   Updated: 2023/09/16 19:40:23 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <math.h>
#include <fcntl.h>
#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>

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
	ft_free_map(vars);
	mlx_destroy_image(vars->m.mlx, vars->img_ptr);
	mlx_destroy_window(vars->m.mlx, vars->m.win);
	exit(EXIT_SUCCESS);
	return (1);
}

int	ft_close(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		ft_free_map(vars);
		mlx_destroy_image(vars->m.mlx, vars->img_ptr);
		mlx_destroy_window(vars->m.mlx, vars->m.win);
		exit(EXIT_SUCCESS);
	}
	return (1);
}

void ft_vars_init(t_vars	*vars)
{
	vars->m.mlx = mlx_init();
	if (!vars->m.mlx)
	{
		perror("Graphical server connecting error");
		ft_free_map(vars);
		exit(EXIT_FAILURE);
	}
	vars->m.win = mlx_new_window(vars->m.mlx, WIDTH, HEIGHT, "FdF");
	if (!vars->m.win)
	{
		perror("Window initializing error");
		ft_free_map(vars);
		exit(EXIT_FAILURE);
	}
	vars->img_ptr = mlx_new_image(vars->m.mlx, WIDTH, HEIGHT);
	if (!vars->img_ptr)
	{
		perror("Image initializing error");
		ft_free_map(vars);
		mlx_destroy_window(vars->m.mlx, vars->m.win);
		exit(EXIT_FAILURE);
	}
	vars->data_addr = mlx_get_data_addr(vars->img_ptr,
			&vars->bpp, &vars->size_line, &vars->endian);
}

void	ft_draw(t_vars *vars)
{
	t_point	point_1;
	t_point	point_2;

	int i = 0, j = 0;
	while (i < vars->map.ordinate)
	{
		j = 0;
		while (j < vars->map.axis)
		{
			printf("%d,0x%X ", vars->map.points[j][i].z, vars->map.points[j][i].color);
			j++;
		}
		printf("\n");
		i++;
	}
	point_1.x = 100;
	point_1.y = 100;
	point_2.x = 150;
	point_2.y = 100;
	ft_draw_line(point_1, point_2, vars);
}

void	ft_hooks(t_vars *vars)
{
	mlx_hook(vars->m.win, 2, 1L << 2, ft_close, vars);
	mlx_hook(vars->m.win, 17, 1L << 17, ft_close_x, vars);
}

char	**ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

void	**ft_free_map(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->map.axis)
	{
		free((vars->map.points)[i]);
		i++;
	}
	free(vars->map.points);
	return (NULL);
}

void	ft_read_map(t_vars *vars, char *file)
{
	int		fd;
	char	*line;
	char	**splitted_line;
	int		x;
	int		y;
	char	**point;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("File open error");
		ft_free_map(vars);
		exit(EXIT_FAILURE);
	}
	y = 0;
	while (y < vars->map.ordinate)
	{
		line = get_next_line(fd);
		if (!line)
		{
			perror("File reading error");
			ft_free_map(vars);
			exit(EXIT_FAILURE);
		}
		splitted_line = ft_split(line, ' ');
		free(line);
		if (!splitted_line)
		{
			perror("Malloc error");
			ft_free_map(vars);
			exit(EXIT_FAILURE);
		}
		x = 0;
		while (x < vars->map.axis)
		{
			point = ft_split(splitted_line[x], ',');
			if (!point)
			{
				perror("Malloc error");
				ft_free_map(vars);
				ft_free_tab(splitted_line);
				exit(EXIT_FAILURE);
			}
			vars->map.points[x][y].z = ft_atoi(point[0]);
			vars->map.points[x][y].color = ft_atoi_hex(point[1]);
			ft_free_tab(point);
			x++;
		}
		y++;
		ft_free_tab(splitted_line);
	}
	if (close(fd) == -1)
	{
		ft_free_map(vars);
		perror("File close error");
		exit(EXIT_FAILURE);
	}
}

void	ft_init_map(t_vars *vars, char *file)
{
	int	i;

	vars->map.points = malloc(sizeof(t_point_arr *) * vars->map.axis);
	if (!vars->map.points)
	{
		perror("Malloc error");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < vars->map.axis)
	{
		vars->map.points[i] = malloc(sizeof(t_point) * vars->map.ordinate);
		if (!vars->map.points[i])
		{
			perror("Malloc error");
			ft_free_map(vars);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	ft_read_map(vars, file);
}

int	ft_count_axis(char *line)
{
	int		axis;
	char	**splitted_line;

	splitted_line = ft_split(line, ' ');
	if (!splitted_line)
	{
		perror("Malloc error");
		exit(EXIT_FAILURE);
	}
	axis = 0;
	while (splitted_line[axis] != NULL)
		axis++;
	ft_free_tab(splitted_line);
	return (axis);
}

int	ft_find_axis(char *file, int *fd)
{
	int		axis;
	char	*first_line;

	*fd = open(file, O_RDONLY);
	if (*fd < 0)
	{
		perror("Open error");
		exit(EXIT_FAILURE);
	}
	first_line = get_next_line(*fd);
	if (!first_line)
	{
		perror("File reading error");
		exit(EXIT_FAILURE);
	}
	axis = ft_count_axis(first_line);
	free(first_line);
	return (axis);
}

int	ft_find_ordinate(int fd, int axis)
{
	int		ordinate;
	char	*line;

	line = get_next_line(fd);
	if (!line)
	{
		perror("File reading error");
		exit(EXIT_FAILURE);
	}
	if (axis != ft_count_axis(line))
	{
		write(2, "Map dimension error\n", 20);
		free(line);
		exit(EXIT_FAILURE);
	}
	ordinate = 2;
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
		if (axis != ft_count_axis(line))
		{
			write(2, "Map dimension error\n", 20);
			free(line);
			exit(EXIT_FAILURE);
		}
		ordinate++;
	}
	free(line);
	if (close(fd) == -1)
	{
		perror("File close error");
		exit(EXIT_FAILURE);
	}
	return (ordinate);
}

void	ft_check_map(char *file, t_vars *vars)
{
	int	fd;

	vars->map.axis = ft_find_axis(file, &fd);
	vars->map.ordinate = ft_find_ordinate(fd, vars->map.axis);
	ft_init_map(vars, file);
}

int	main(int argc, char **argv)
{
	t_vars	*vars;

	if (argc == 2)
	{
		vars = &(t_vars){0};
		ft_check_map(argv[1], vars);
		ft_vars_init(vars);
		ft_draw(vars);
		mlx_put_image_to_window(vars->m.mlx, vars->m.win, vars->img_ptr, 0, 0);
		ft_hooks(vars);
		mlx_loop(vars->m.mlx);
	}
	write(2, "Usage: ./fdf <filename>\n", 24);
	return (0);
}
