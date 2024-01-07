/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:00:41 by vda-conc          #+#    #+#             */
/*   Updated: 2024/01/07 14:53:25 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	***ft_create_map_from_file(int fd)
{
	char	***map;
	char	*line;
	char	**points;
	int		i;

	i = 0;
  map = NULL;
	line = get_next_line(fd);
	if (line)
	{
		while (line)
		{
			points = ft_split(line, ' ');
			ft_trim_nl(points);
      map = ft_add_map_line(map, points);
			line = get_next_line(fd);
			if (line == NULL)
				break ;
			i++;
		}
	}
	else
		return (NULL);
  return (map);
}

void print_map(char ***map) {
    int i = 0, j;
    while (map[i]) {
        j = 0;
        while (map[i][j]) {
            printf("%s ", map[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
}

void	ft_trim_nl(char **points)
{
	int	i;
	int	j;

	if (!points)
		return ;
	i = 0;
	while (points[i])
	{
		j = 0;
		while (points[i][j])
		{
			if (points[i][j] == '\n')
				points[i][j] = '\0';
			j++;
		}
		i++;
	}
}

char ***ft_add_map_line(char ***map, char **newline)
{
  char ***new_map;

  if (!map)
  {
    new_map = malloc(2 * sizeof (char**));
    if (!new_map)
      return (NULL);
    new_map[0] = newline;
    new_map[1] = NULL;
  }
  else
  {
    new_map = ft_join_map(map, newline);
  }
  return (new_map);
}

char ***ft_join_map(char ***old_map, char** new_line)
{
  char ***new_map;
  int old_map_size;
  int i;

  old_map_size = ft_maplen(old_map);
  new_map = malloc((old_map_size + 2) * sizeof(char**));
  if (!new_map)
    return NULL;
  i = 0;
  while (old_map[i])
  {
    new_map[i] = old_map[i];
    i++;
  }
  new_map[i] = new_line;
  new_map[i + 1] = NULL;
  free(old_map);
  return (new_map);
}

int ft_linelen(char **line)
{
  int i;

  i = 0;

  while(line[i])
    i++;
  return (i);
}
int ft_maplen(char ***map)
{
	int	i;

	if (!map)
  	return (0);
  i = 0;
	while (map[i])
  {
		i++;
  }
	return (i);
}
