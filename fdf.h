#ifndef FDF_H
# define FDF_H

# include "./gnl/get_next_line.h"
# include "./libft/libft.h"
# include "./minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
#include <math.h>
// STRUCT //

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

// MAIN FUNCTION //
int			ft_fdf(char ***map);

// PARSING //
int			ft_maplen(char ***map);
char	***ft_join_map_lines(char ***map, char **new_line);
char		***ft_create_map_from_file(int fd);
int			ft_valid_file(char *file_name);
char		*remove_spaces_and_newlines(char *str);
char ***copy_map_content(char ***map, char ***new_map, char **new_line, int maplen);
int			get_map_length(char ***map);
int get_line_length(char **new_line);
void ft_trim_nl(char **points);
char ***ft_add_map_line(char ***map, char **newline);
char ***ft_join_map(char ***old_map, char** new_line);
char **ft_null_line(int line_len);
int ft_linelen(char **line);
void print_map(char ***map);
// MEMORY //
void		ft_free_memory(char **tab);
void		free_old_map(char ***map, int maplen);
char    ***allocate_new_map(int maplen, int line_length);
// DEBUG //
void		ft_print_all_lines(char **lines_tab);

// CALCULATIONS //
double ft_first_rot_x(int x, int y);
double ft_first_rot_y(int x, int y);
double ft_arc_tan_x(double x);
double ft_arc_tan_y(double x, double y, int z);

// GRAPHICS //
void		draw_grid_from_matrix(t_data *data, char ***map, int grid_spacing,
				int color);
void		bresenham(int x1, int y1, int x2, int y2, t_data *img);
void		draw_line(char ***map, t_data *img);

#endif
