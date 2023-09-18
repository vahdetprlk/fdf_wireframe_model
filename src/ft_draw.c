/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 17:05:37 by vparlak           #+#    #+#             */
/*   Updated: 2023/09/18 19:56:11 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>



void	orjin_delta(t_point *point, int orjin_x, int orjin_y)
{
	point->x = point->x + orjin_x;
	point->y = point->y + orjin_y;
}

t_point	ft_rotation_2d(t_point p1, int teta)
{
	t_point	tmp_point;

	teta %= 360;

	tmp_point.x = (p1.x * cos(teta * (M_PI / 180))) - (p1.y * sin(teta * (M_PI / 180)));
	tmp_point.y = (p1.x * sin(teta * (M_PI / 180))) + (p1.y * cos(teta * (M_PI / 180)));
	return(tmp_point);
}

void	ft_draw(t_vars *vars, int angle)
{
	t_point	point_1;

	t_point	point_4;

	point_1.x = 300;
	point_1.y = 300;
	point_4.x = 300;
	point_4.y = 400;
		ft_draw_line(point_1, point_4, vars);
			point_4.x = point_4.x - point_1.x;
			point_4.y = point_4.y - point_1.y;
			point_4 = ft_rotation_2d(point_4, angle);
			point_4.x = point_4.x + point_1.x;
			point_4.y = point_4.y + point_1.y;
		ft_draw_line(point_1, point_4, vars);
}
