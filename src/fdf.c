/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 20:12:30 by vparlak           #+#    #+#             */
/*   Updated: 2023/08/16 20:22:21 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <math.h>

#define WIDTH 800
#define HEIGHT 600
// Yardımcı fonksiyonlar
int ft_abs(int x)
{
    if (x < 0)
        x = -x;
    return (x);
}
float	fpart(float x)
{
    return x - floor(x);
}
float	rfpart(float x)
{
    return 1.0 - fpart(x);
}
int	ipart(float x)
{
    return (int)x;
}
void draw_pixel(int x, int y, float brightness, void *mlx_ptr, void *win_ptr) {
    int color = (int)(brightness * 255); // Parlaklığı renk değerine dönüştür
    int pixel_color = (color << 16) | (color << 8) | color; // RGB formatına dönüştür
    mlx_pixel_put(mlx_ptr, win_ptr, x, y, pixel_color);
}
void draw_line(int x0, int y0, int x1, int y1, void *mlx_ptr, void *win_ptr) {
    int dx = ft_abs(x1 - x0);
    int dy = ft_abs(y1 - y0);
    int is_steep = dy > dx;
    if (is_steep) {
        // Swap x0 with y0 and x1 with y1
        int temp = x0;
        x0 = y0;
        y0 = temp;
        temp = x1;
        x1 = y1;
        y1 = temp;
    }
    if (x0 > x1) {
        // Swap x0 with x1 and y0 with y1
        int temp = x0;
        x0 = x1;
        x1 = temp;
        temp = y0;
        y0 = y1;
        y1 = temp;
    }
    dx = x1 - x0;
    dy = y1 - y0;
    float gradient = (float)dy / dx;
    // First endpoint
    float x_end = round(x0);
    float y_end = y0 + gradient * (x_end - x0);
    float x_gap = rfpart(x_end);
    float y_gap = rfpart(y_end);
    int x_pixel1 = (int)x_end;
    int y_pixel1 = (int)y_end;
    if (is_steep) {
        draw_pixel(y_pixel1, x_pixel1, y_gap * x_gap, mlx_ptr, win_ptr);
        draw_pixel(y_pixel1 + 1, x_pixel1, fpart(y_end) * x_gap, mlx_ptr, win_ptr);
    } else {
        draw_pixel(x_pixel1, y_pixel1, y_gap * x_gap, mlx_ptr, win_ptr);
        draw_pixel(x_pixel1, y_pixel1 + 1, fpart(y_end) * x_gap, mlx_ptr, win_ptr);
    }
    float intery = y_end + gradient; // First y-intersection for the main loop
    // Second endpoint
    x_end = round(x1);
    y_end = y1 + gradient * (x_end - x1);
    x_gap = fpart(x1 + 0.5);
    int x_pixel2 = (int)x_end;
    int y_pixel2 = (int)y_end;
    if (is_steep) {
        draw_pixel(y_pixel2, x_pixel2, y_gap * x_gap, mlx_ptr, win_ptr);
        draw_pixel(y_pixel2 + 1, x_pixel2, fpart(y_end) * x_gap, mlx_ptr, win_ptr);
    } else {
        draw_pixel(x_pixel2, y_pixel2, y_gap * x_gap, mlx_ptr, win_ptr);
        draw_pixel(x_pixel2, y_pixel2 + 1, fpart(y_end) * x_gap, mlx_ptr, win_ptr);
    }
    // Main loop
    if (is_steep) {
        for (int x = x_pixel1 + 1; x <= x_pixel2 - 1; x++) {
            draw_pixel(ipart(intery), x, rfpart(intery), mlx_ptr, win_ptr);
            draw_pixel(ipart(intery) + 1, x, fpart(intery), mlx_ptr, win_ptr);
            intery += gradient;
        }
    } else {
        for (int x = x_pixel1 + 1; x <= x_pixel2 - 1; x++) {
            draw_pixel(x, ipart(intery), rfpart(intery), mlx_ptr, win_ptr);
            draw_pixel(x, ipart(intery) + 1, fpart(intery), mlx_ptr, win_ptr);
            intery += gradient;
        }
    }
}
int main() {
    void *mlx_ptr = mlx_init();
    void *win_ptr = mlx_new_window(mlx_ptr, WIDTH, HEIGHT, "Wu Line Drawing Example");
    draw_line(0, 0, 10, 5, mlx_ptr, win_ptr);
    draw_line(200, 700, 700, 0, mlx_ptr, win_ptr);
    mlx_loop(mlx_ptr);
    return 0;
}
