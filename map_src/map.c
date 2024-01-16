/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:00:41 by vda-conc          #+#    #+#             */
/*   Updated: 2024/01/16 09:37:51 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

char	***ft_create_map_from_file(int fd)
{
	char	***map;
	char	*line;
	char	**points;

	int (i) = 0;
	map = NULL;
	line = get_next_line(fd);
	if (line)
	{
		while (line)
		{
			points = ft_split(line, ' ');
			ft_trim_nl(points);
			map = ft_add_map_line(map, points);
			if (!map)
				return (NULL);
			free(line);
			line = get_next_line(fd);
			if (line == NULL && i++ && read(fd, NULL, 1) == 1)
				return (ft_free_map(map), NULL);
		}
	}
	else
		return (NULL);
	return (map);
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

char	***ft_add_map_line(char ***map, char **newline)
{
	char	***new_map;

	if (!newline)
		return (NULL);
	if (!map)
	{
		new_map = malloc(2 * sizeof(char **));
		if (!new_map)
			return (NULL);
		new_map[0] = newline;
		new_map[1] = NULL;
	}
	else
	{
		new_map = ft_join_map(map, newline);
		if (!new_map)
			return (NULL);
	}
	return (new_map);
}

t_point	*ft_convert_point(int x, int y, char *z)
{
	t_point	*point;
	char	**split;

	point = malloc(sizeof(t_point));
	if (!point)
		return (NULL);
	point->x = x;
	point->y = y;
	if (!ft_find_coma(z))
	{
		point->color = -1;
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

t_origin	ft_define_origin(t_point ***map)
{
	int			row_index;
	int			col_index;
	t_origin	origin;

	row_index = ft_define_mid_row(map);
	col_index = ft_define_mid_col(map);
	origin.row_index = row_index;
	origin.col_index = col_index;
	return (origin);
}
