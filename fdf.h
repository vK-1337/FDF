#ifndef FDF_H
# define FDF_H

# include "./gnl/get_next_line.h"
# include <math.h>
# include "./libft/libft.h"
# include "./minilibx-linux/mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>

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
int		ft_fdf(char **map);

// PARSING //
int		ft_maplen(char **map);
char	**ft_join_map_lines(char **map, char *new_line);
char	**ft_create_map_from_file(int fd);
int		ft_valid_file(char *file_name);

// MEMORY //
void	ft_free_memory(char **tab);

// DEBUG //
void	ft_print_all_lines(char **lines_tab);

// GRAPHICS //
void ft_print_triangle(t_data *img);
void dessinerCercle(int centreX, int centreY, int rayon, t_data *img);
void dessinerCercleContours(int centreX, int centreY, int rayon, t_data *img);
void dessinerCercleContoursFin(int centreX, int centreY, int rayon, t_data *img);
int interpolationCouleur(int couleurDepart, int couleurArrivee, float ratio);
void dessinerCercleAvecGradient(int centreX, int centreY, int rayon, t_data *img, int couleurDepart, int couleurArrivee);
void ft_grid(char **map, t_data *img);

#endif
