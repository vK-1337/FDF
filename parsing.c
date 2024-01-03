/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:13:54 by vda-conc          #+#    #+#             */
/*   Updated: 2024/01/03 18:10:42 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_parse_map(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
  if (fd == -1)
    return (write(2, "Invalid file\n", 14), -1);
  if (ft_check_map_validity(fd) == -1)
    return (write(2, "Map is not valid\n", 18), -1);
  return (0);
}

int ft_check_map_validity(int fd)
{
  char *line;
  int i;
  char ***lines_tab;

  lines_tab = malloc(10 * sizeof(char*));
  line = get_next_line(fd);
  i = 0;
  lines_tab[i] = ft_split(line, ' ');
  free(line);
  while (line)
  {
    line = get_next_line(fd);
    if (line == NULL)
      break;
    lines_tab[++i] = ft_split(line, ' ');
    free(line);
  }
  free(line);
  ft_print_all_lines(lines_tab);
  i = 0;
  while (i < 9)
  {
    free(lines_tab[i++]);
  }
  free(lines_tab);
  return (0);
}
ft_create_map_from_file(int fd)
{
    char ***map;
    char *line;
}
void ft_print_all_lines(char ***lines_tab)
{
  int i;
  int j;

  i = 0;
  while (lines_tab[i])
  {
    j = 0;
    while (lines_tab[i][j])
    {
      printf("%s", lines_tab[i][j]);
      free(lines_tab[i][j++]);
    }
    i++;
  }
}
