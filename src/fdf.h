/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:48:47 by vparlak           #+#    #+#             */
/*   Updated: 2023/09/22 01:03:23 by vparlak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIDTH 1920
# define HEIGHT 1080

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}	t_mlx;

typedef struct s_point
{
	float	x;
	float	y;
	t_color	color;
}	t_point;

typedef struct s_render_map
{
	float	x;
	float	y;
	float	z;
}	t_render_map;

typedef struct s_point_arr
{
	int	z;
	int	color;
}	t_point_arr;

typedef struct s_map
{
	t_point_arr	**points;
	int			axis;
	int			ordinate;
}	t_map;

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}	t_color;


typedef struct s_vars
{
	t_mlx			m;
	t_map			map;
	t_render_map	**r_map;
	t_point			origin;
	char			*data_addr;
	int				size_line;
	int				bpp;
	int				endian;
	void			*img_ptr;
	float			x_offset;
	float			y_offset;
	float			offset;
	int				i;
	int				j;
	int				angle;
	int				min_z;
	int				max_z;
	int				projection;
}	t_vars;

char	**ft_split(char const *s, char c);
char	**ft_free_tab(char **tab);
void	**ft_free_map_point(t_vars *vars);
void	**ft_free_r_map(t_vars *vars);
int		ft_atoi(const char *str);
int		ft_atoi_hex(const char *str);
void	*ft_calloc(int count, int size);
void	ft_bzero(void *s, int n);
void	ft_draw_line(t_point point_1, t_point point_2, t_vars *vars);

float	ft_fpart(float x);
float	ft_rfpart(float x);
int		ft_ipart(float x);
int		ft_abs(int x);

int		ft_count_axis(char *line);
void	ft_read_map(t_vars *vars, char *file);
void	ft_check_map(char *file, t_vars *vars);
void	ft_check_axis(char *line, int axis);

void	ft_vars_init(t_vars	*vars);
void	ft_hooks(t_vars *vars);

void	ft_file_close(int fd, t_vars *vars);
void	ft_error(char *msg, t_vars *vars, char **splitted_str, int status);

void	ft_draw(t_vars *vars);
void	ft_projection_iso(t_vars *vars);

#endif
