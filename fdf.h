#ifndef FDF_H
# define FDF_H

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

# define WIDTH 1920
# define HEIGHT 1080
# define CENTER_X 960
# define CENTER_Y 540
# define ISOMETRIC 45
# define PARALLEL 0
# define SPACE 30

// STRUCT //
typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

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
	t_data	*img;
	t_point	***map;
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

// MAIN FUNCTION //
int			ft_fdf(t_point ***map);

// PARSING //
int			ft_maplen(char ***map);
char		***ft_create_map_from_file(int fd);
int			ft_valid_file(char *file_name);
void		ft_trim_nl(char **points);
char		***ft_add_map_line(char ***map, char **newline);
char		***ft_join_map(char ***old_map, char **new_line);
int			ft_linelen(char **line);
t_point		***ft_convert_map(char ***map);
void		ft_print_struct_map(t_point ***struct_map);
t_point		*ft_convert_point(int x, int y, char *z);
int			ft_struct_map_len(t_point ***map);
int			ft_struct_linelen(t_point **line);
int			ft_define_mid_row(t_point ***map);
int			ft_define_mid_col(t_point ***map);
t_origin	ft_define_origin(t_point ***map);
int			ft_find_coma(char *str);
void		ft_points_spacing(t_point ***map);

// MEMORY //
void		ft_free_memory(char **tab);
void		free_old_map(char ***map, int maplen);
char		***allocate_new_map(int maplen, int line_length);

// DEBUG //
void		ft_print_all_lines(char **lines_tab);
void		print_map(char ***map);

// CALCULATIONS //
void		ft_rotate_x(t_point *point, double sin_theta, double cos_theta);
void		ft_rotate_z(t_point *point, double sin_theta, double cos_theta,
				int x_space, int y_space);
void		ft_cast_point(t_point *point, int angle, int x_space, int y_space);
void		ft_cast_whole_map(t_point ***map, int angle, int space);
void		ft_rotate_map_z(t_point ***map, double angle);
void		ft_rotate_map_x(t_point ***map, double angle);
void		ft_rotate_map_y(t_point ***map, double angle);
void		ft_points_spacing(t_point ***map);

// GRAPHICS //
void		draw_grid_from_matrix(t_data *data, char ***map, int grid_spacing,
				int color);
void	bresenham(int x1, int y1, int x2, int y2, t_data *img, long color);
void		draw_line(t_point ***map, t_data *img);
int			ft_render(t_hook_data *redraw);

// BONUS FUNCTIONS //
void		ft_zoom_in(t_hook_data *redraw);
void		ft_zoom_out(t_hook_data *redraw);
void		ft_move_up(t_point ***map, t_positions *positions);
void		ft_move_down(t_point ***map, t_positions *positions);
void		ft_move_left(t_point ***map, t_positions *positions);
void		ft_move_right(t_point ***map, t_positions *positions);

#endif
