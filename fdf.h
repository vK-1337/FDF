#ifndef FDF_H
# define FDF_H

# include "./gnl/get_next_line.h"
# include "./libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>

// PARSING //
int		ft_parse_map(char *file_name);
int		ft_check_map_validity(int fd);
int		ft_maplen(char **map);
char	**ft_join_map_lines(char **map, char *new_line);
char	**ft_create_map_from_file(int fd);

// MEMORY //
int		ft_free_memory(char **tab);

// DEBUG //
void	ft_print_all_lines(char **lines_tab);

#endif
