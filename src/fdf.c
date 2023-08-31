/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:53:27 by vparlak           #+#    #+#             */
/*   Updated: 2023/08/31 18:31:30 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "safeAlloc.h"

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

int	ft_close_x(void)
{
	exit(0);
	return (1);
}

int	ft_close(int keycode)
{
	if (keycode == 53)
		exit(0);
	return (1);
}

void ft_vars_init(t_vars	*vars)
{
	vars->m.mlx = mlx_init();
	if (!vars->m.mlx)
		exit(EXIT_FAILURE);
	vars->m.win = mlx_new_window(vars->m.mlx, 1600, 1600, "My Window");
	if (!vars->m.win)
		exit(EXIT_FAILURE);
	vars->img_ptr = mlx_new_image(vars->m.mlx, 1600, 1600);
	if (!vars->img_ptr)
		exit(EXIT_FAILURE);
	vars->data_addr = mlx_get_data_addr(vars->img_ptr,
			&vars->bpp, &vars->size_line, &vars->endian);
	if (!vars->data_addr)
		exit(EXIT_FAILURE);
}

void	ft_draw_polygon(int sides, double radius, int origin[], t_vars *vars)
{
	double angle = 360.0 / sides;
	t_point points[sides];

	for (int i = 0; i < sides; i++) {
		double x = origin[0] + radius * cos(i * angle * M_PI / 180.0);
		double y = origin[1] + radius * sin(i * angle * M_PI / 180.0);
		points[i].x = round(x);
		points[i].y = round(y);
	}

	for (int i = 0; i < sides; i++) {
		ft_draw_line(points[i], points[(i + 1) % sides], vars);
	}
}

void	ft_draw_random_polygons(int num_polygons, t_vars *vars)
{
	srand(time(NULL)); // Rastgele sayılar için tohumu ayarla

	for (int i = 0; i < num_polygons; i++) {
		int sides = rand() % 10 + 3; // Kenar sayısı 3 ile 12 arasında rastgele
		double radius = rand() % 70 + 30; // Yarıçap 30 ile 100 arasında rastgele
		int origin[2] = { rand() % 1600, rand() % 800 }; // Rastgele orijin koordinatları
		ft_draw_polygon(sides, radius, origin, vars);
	}
}

void	ft_draw(t_vars *vars)
{
	t_point p1;
	t_point p2;
	t_point p3;
	t_point p4;
	t_point p5;


	// ft_draw_polygon(4, 150, (int [2]){400, 300}, vars);
	// ft_draw_polygon(50, 100, (int [2]){500, 90}, vars);
	// ft_draw_polygon(50, 100, (int [2]){280, 90}, vars);
	ft_draw_polygon(900, 180, (int [2]){600, 180}, vars);
	// ft_draw_polygon(25, 130, (int [2]){100, 270}, vars);
	// ft_draw_polygon(25, 140, (int [2]){200, 560}, vars);
	// ft_draw_polygon(10, 100, (int [2]){200, 650}, vars);


	p1.x = 400;
	p1.y = 400;
	p2.x = 800;
	p2.y = 400;
	p3.x = 800;
	p3.y = 800;
	p4.x = 400;
	p4.y = 800;
	p5.x = p3.x * 1.30;
	p5.y = p3.y / 1.90;
	ft_draw_line(p1, p2, vars);
	ft_draw_line(p2, p3, vars);
	ft_draw_line(p3, p4, vars);
	ft_draw_line(p4, p1, vars);
	ft_draw_line(p3, p5, vars);
	mlx_put_image_to_window(vars->m.mlx, vars->m.win, vars->img_ptr, 0, 0);
}

void	ft_hooks(t_vars **vars)
{
	mlx_hook((*vars)->m.win, 2, 1L << 2, ft_close, vars);
	mlx_hook((*vars)->m.win, 17, 1L << 17, ft_close_x, vars);
}

int	main()
{
	t_vars	*vars;

	vars = &(t_vars){0};
	ft_vars_init(vars);
	ft_draw(vars);
	ft_hooks(&vars);
	mlx_loop(vars->m.mlx);
}
