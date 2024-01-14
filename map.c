/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:00:41 by vda-conc          #+#    #+#             */
/*   Updated: 2024/01/14 17:38:50 by vda-conc         ###   ########.fr       */
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
      if (!points)
        return (free(line), NULL);
			ft_trim_nl(points);
      map = ft_add_map_line(map, points);
      free(line);
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
  if (!line)
    return (i);
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


t_point ***ft_convert_map(char ***map)
{
  int i;
  int j;
  t_point ***new_map;

  new_map = malloc((ft_maplen(map) + 1) * sizeof (t_point **));
  i = 0;
  while (map[i])
  {
    new_map[i] = malloc((ft_linelen(map[i]) + 1) * (sizeof (t_point *)));
    j = 0;
    while (map[i][j])
    {
      new_map[i][j] = ft_convert_point(j, i, map[i][j]);
      j++;
    }
    new_map[i][j] = NULL;
    i++;
  }
  new_map[i] = NULL;
  return (new_map);
}

t_point *ft_convert_point(int x, int y, char *z)
{
  t_point *point;
  char **split;

  point = malloc(sizeof(t_point));
  if (!point)
    return (NULL);
  point->x = x;
  point->y = y;
  if(!ft_find_coma(z))
  {
    point->color = 0;
    point->z = ft_atoi(z);
  }
  else
  {
    split = ft_split(z, ',');
    point->z = ft_atoi(split[0]);
    point->color = strtol(split[1], NULL, 16);
    ft_free_memory(split);
  }
  return (point);
}

int ft_find_coma(char *str)
{
  int i;

  i = 0;
  while (str[i])
  {
    if (str[i] == ',')
      return (1);
    i++;
  }
  return (0);
}

int ft_struct_map_len(t_point ***map)
{
  int i;
  if (!map)
    return (0);
  i = 0;
  while (map[i])
    i++;
  return (i);
}

int			ft_struct_linelen(t_point **line)
{
  int	i;

  if (!line)
    return (0);
  i = 0;
  while (line[i])
    i++;
  return (i);
}

t_origin ft_define_origin(t_point ***map)
{
  int row_index;
  int col_index;
  t_origin origin;

  row_index = ft_define_mid_row(map);
  col_index = ft_define_mid_col(map);
  origin.row_index = row_index;
  origin.col_index = col_index;
  printf("origin.row_index = %d\n", origin.row_index);
  printf("origin.col_index = %d\n", origin.col_index);
  return (origin);
}

int ft_define_mid_col(t_point ***map)
{
  int mid_col;
  int map_line_len;

  map_line_len = ft_struct_linelen(map[0]);
  if (map_line_len % 2 == 0)
    mid_col = (map_line_len / 2) - 1;
  else
    mid_col = map_line_len / 2;
  return (mid_col);
}

int ft_define_mid_row(t_point ***map)
{
  int mid_row;
  int map_len;

  map_len = ft_struct_map_len(map);
  if (map_len % 2 == 0)
    mid_row = (map_len / 2) - 1;
  else
    mid_row = map_len / 2;
  return (mid_row);
}

void ft_free_map(char ***map)
{
  int i;
  int j;

  i = 0;
  while (map[i])
  {
    j = 0;
    while (map[i][j])
    {
      free(map[i][j]);
      j++;
    }
    free(map[i]);
    i++;
  }
  free(map);
}

void ft_free_struct_map(t_point ***map)
{
  int i;
  int j;

  i = 0;
  while (map[i])
  {
    j = 0;
    while (map[i][j])
    {
      free(map[i][j]);
      j++;
    }
    free(map[i]);
    i++;
  }
  free(map);
}