/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:01:41 by vda-conc          #+#    #+#             */
/*   Updated: 2024/01/25 13:16:38 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

// INCLUDES //
# include "./gnl/get_next_line.h"
# include "./libft/libft.h"
# include "./minilibx-linux/mlx.h"
# include <X11/X.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>

// MACROS //

# define WIDTH 1920
# define HEIGHT 1080
# define CENTER_X 960
# define CENTER_Y 540
# define ISOMETRIC 45
# define PARALLEL 0
# define SPACE 30
# define DEFAULT_COLOR 0xFF0000

// STRUCTURES  //
typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_spaces
{
	int		x_space;
	int		y_space;
}			t_spaces;

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
	int		x_space;
	int		y_space;
	long	color;
}			t_point;

typedef struct s_redraw
{
	t_point	***map;
	t_data	*img;
	void	*mlx;
	void	*mlx_win;
}			t_redraw;

typedef struct s_hook_data
{
	void	*mlx;
	void	*mlx_win;
	int		mouse_x;
	int		mouse_y;
	int		mouse_one_pressed;
	int		mouse_two_pressed;
	int		shift_pressed;
	int		berserk_map;
	int		r_key_pressed;
	int		any_key_pressed;
	t_data	*img;
	t_point	***map;
	t_point	***original_map;
}			t_hook_data;

typedef struct s_positions
{
	int		old_x;
	int		old_y;
	int		new_x;
	int		new_y;
}			t_positions;

typedef struct s_origin
{
	int		row_index;
	int		col_index;
}			t_origin;

typedef struct s_colors
{
	int		start_red;
	int		start_green;
	int		start_blue;
	int		end_red;
	int		end_green;
	int		end_blue;
	int		red;
	int		green;
	int		blue;
}			t_colors;

typedef struct s_bres_data
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		err2;
	double	distance;
	double	ratio;
	double	increment;
	int		color;
	int		x1;
	int		y1;
	int		x2;
	int		y2;
}			t_bres_data;

// STRUCTURES END //

// MAIN FUNCTION //
int			ft_fdf(t_point ***map, int is_berserk_map);

// ANIMATIONS //
void		ft_berserk_animation(t_hook_data *data);
void ft_change_color(t_hook_data *data, int call_count);

// MAP && PARSING //
int			ft_maplen(char ***map);
int			ft_linelen(char **line);
int			ft_struct_map_len(t_point ***map);
int			ft_struct_linelen(t_point **line);
int			ft_find_coma(char *str);
char		***ft_create_map_from_file(int fd);
int			ft_valid_file(char *file_name);
void		ft_trim_nl(char **points);
char		***ft_add_map_line(char ***map, char **newline);
char		***ft_join_map(char ***old_map, char **new_line);
t_point		***ft_convert_map(char ***map);
t_point		*ft_convert_point(int x, int y, char *z);
int			ft_define_mid_row(t_point ***map);
int			ft_define_mid_col(t_point ***map);
void		ft_draw_commands(void *mlx_ptr, void *win_ptr);
t_point		***ft_copy_map(t_point ***map);
t_point		*ft_copy_point(t_point *point);
int			ft_point_lesser(int point_one, int point_two);
int			ft_is_berserk_map(char *str);
void		ft_color_map(t_point ***map);
int			ft_colored_map(t_point ***map);
t_origin	ft_define_origin(t_point ***map);

// MEMORY //
void		ft_free_struct_map(t_point ***map);
void		ft_free_map(char ***map);
void		ft_free_data(t_hook_data *data);
int			ft_close_win(void *params);
void		ft_free_memory(char **tab);
void		free_old_map(char ***map, int maplen);
char		***allocate_new_map(int maplen, int line_length);

// ASSIGNATONS //
void		ft_assign_data(t_hook_data *data, t_point ***map, void *mlx,
				void *mlx_win);
void		ft_assign_bres_data(t_bres_data *bres_data, t_point point_one,
				t_point point_two);

// SPACING //
void		ft_points_spacing(t_point ***map);
void		ft_define_spacing(int i, int j, t_origin origin, t_point ***map);

// PROJECTIONS //
void		ft_iso_projection(t_hook_data *data);
void		ft_parallel_projection(t_hook_data *data);

// BRESENHAM //
int			ft_render(t_hook_data *data);
void		bresenham(t_point point_one, t_point point_two, t_data *img);
void		draw_line(t_point ***map, t_data *img);
int			get_color(int start_color, int end_color, double ratio);
int			interpolate(int start, int end, double ratio);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);

// ZOOMS AND ADUSTMENTS //
void		ft_zoom_adjust(t_point ***map);
void		ft_zoom_in(t_hook_data *redraw);
void		ft_zoom_out(t_hook_data *redraw);
void		ft_center_for_parallel(t_point ***map);
void		ft_center_whole_map(t_point ***map);
void		ft_center_x(t_point ***map, t_point *middle_point, int x_movement);
void		ft_center_y(t_point ***map, t_point *middle_point, int y_movement);

// MOVES AND ROTATIONS //
void		ft_move_up(t_point ***map, t_positions *positions);
void		ft_move_down(t_point ***map, t_positions *positions);
void		ft_move_left(t_point ***map, t_positions *positions);
void		ft_move_right(t_point ***map, t_positions *positions);
void		ft_move_right_up(t_hook_data *data, t_positions *positions);
void		ft_move_right_down(t_hook_data *data, t_positions *positions);
void		ft_move_left_up(t_hook_data *data, t_positions *positions);
void		ft_move_left_down(t_hook_data *data, t_positions *positions);
void		ft_rotate_x(t_point *point, double sin_theta, double cos_theta);
void		ft_rotate_z(t_point *point, double sin_theta, double cos_theta,
				t_spaces *spaces);
void		ft_cast_point(t_point *point, int angle, int x_space, int y_space);
void		ft_cast_whole_map(t_point ***map, int angle, int space);
void		ft_rotate_map_z(t_point ***map, double angle);
void		ft_rotate_map_x(t_point ***map, double angle);
void		ft_rotate_map_y(t_point ***map, double angle);

// KEYS //
int			ft_handle_key_pressed(int key, t_hook_data *data);
int			ft_handle_key_released(int key, t_hook_data *data);
void		ft_handle_x(t_hook_data *data);
void		ft_handle_y(t_hook_data *data);
void		ft_handle_z(t_hook_data *data);
void		ft_arrow_moves(t_hook_data *data, int key);

// MOUSE //
void		ft_mouse_rotate_x_y(t_hook_data *data, double x_angle,
				double y_angle);
int			ft_handle_mouse_motion(int x, int y, t_hook_data *data);
int			ft_handle_mouse_release(int button, int x, int y,
				t_hook_data *data);
int			ft_handle_mouse_press(int button, int x, int y, t_hook_data *data);
void		ft_mouse_two(t_hook_data *data, int old_x, int old_y);
void		ft_mouse_one(t_hook_data *data, t_positions *positions, int old_x,
				int old_y);

// HOOKS //
void		ft_set_hooks(t_hook_data *data);

#endif
