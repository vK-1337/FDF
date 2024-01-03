/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:13:54 by vda-conc          #+#    #+#             */
/*   Updated: 2024/01/03 21:13:41 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

ft_parse_file(int fd)
{
  int i;

}
char **ft_create_map_from_file(int fd)
{
    char **map;
    char *line;
    int i;

    map = NULL;
    if (!map)
      return (NULL);
    i = 0;
    line = get_next_line(fd);
    if (line)
    {
      while (line)
      {
        map[i++] = line;
        free(line);
        line = get_next_line(fd);
        if (line == NULL)
          return (ft_free_memory(map), NULL);
      }
    }
    else
      return (NULL);
    return (map);
}

char **ft_join_map_lines(char **map, char* new_line)
{
  // Prendre la map deja existante map[[line1],[line2], [line3], [line4]];
  // et lui ajouter new_line;
  // Allouer un element de plus a map deja existance
  // puis join la new_line
}

int	ft_free_memory(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (1);
}
