/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 17:05:37 by vparlak           #+#    #+#             */
/*   Updated: 2023/09/18 23:44:58 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>



void	orjin_delta(t_point *point, int orjin_x, int orjin_y)
{
	point->x = point->x + orjin_x;
	point->y = point->y + orjin_y;
}

t_point	ft_rotation_2d(t_point p1, t_point origin, int teta)
{
	t_point	tmp_point;

	teta %= 360;
	p1.x = p1.x - origin.x;
	p1.y = p1.y - origin.y;
	tmp_point.x = (p1.x * cos(teta * (M_PI / 180))) - (p1.y * sin(teta * (M_PI / 180)));
	tmp_point.y = (p1.x * sin(teta * (M_PI / 180))) + (p1.y * cos(teta * (M_PI / 180)));
	tmp_point.x = tmp_point.x + origin.x;
	tmp_point.y = tmp_point.y + origin.y;
	return(tmp_point);
}

void	ft_draw(t_vars *vars)
{
	t_point	origin;
	t_point	point_1;
	t_point	point_2;
	t_point	point_3;
	t_point	point_4;
	t_point	point_5;
	t_point	point_6;

	origin.x = 300;
	origin.y = 300;

	point_1.x = 300;
	point_1.y = 250;

	point_2.x = 400;
	point_2.y = 300;

	point_3.x = 400;
	point_3.y = 400;

	point_4.x = 300;
	point_4.y = 400;

	point_5.x = 300;
	point_5.y = 500;

	point_6.x = 400;
	point_6.y = 500;



	point_6 = ft_rotation_2d(point_6, point_2, 30);
	point_3 = ft_rotation_2d(point_3, point_2, 30);
	point_2 = ft_rotation_2d(point_2, origin, 30);
	point_4 = ft_rotation_2d(point_4, origin, 30);
	point_5 = ft_rotation_2d(point_5, origin, 30);


	point_4 = ft_rotation_2d(point_4, origin, 30);
	point_5 = ft_rotation_2d(point_5, origin, 30);
	point_6 = ft_rotation_2d(point_6, origin, 30);
	point_3 = ft_rotation_2d(point_3, origin, 30);

	point_4.y -= 50;
	point_2.y -= 50;

	ft_draw_line(point_1, point_2, vars);
	ft_draw_line(point_2, point_3, vars);
	ft_draw_line(point_3, point_4, vars);
	ft_draw_line(point_4, point_1, vars);
	ft_draw_line(point_4, point_5, vars);
	ft_draw_line(point_5, point_6, vars);
	ft_draw_line(point_6, point_3, vars);



}
