#ifndef FDF_H
# define FDF_H

# include "./libft/libft.h"
#include "./gnl/get_next_line.h"
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>

// PARSING //
int	ft_parse_map(char *file_name);
int ft_check_map_validity(int fd);

// DEBUG //
void ft_print_all_lines(char ***lines_tab);

#endif
