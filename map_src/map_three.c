/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_three.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:03:15 by vda-conc          #+#    #+#             */
/*   Updated: 2024/01/15 12:49:53 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	ft_points_spacing(t_point ***map)
{
	int			j;
	int			i;
	t_origin	origin;

	origin = ft_define_origin(map);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			ft_define_spacing(i, j, origin, map);
			j++;
		}
		i++;
	}
}

void	ft_define_spacing(int i, int j, t_origin origin, t_point ***map)
{
	if (i < origin.row_index)
		map[i][j]->y_space = (i - origin.row_index) * SPACE;
	else if (i > origin.row_index)
		map[i][j]->y_space = (i - origin.row_index) * SPACE;
	else
		map[i][j]->y_space = 0;
	if (j < origin.col_index)
		map[i][j]->x_space = (j - origin.col_index) * SPACE;
	else if (j > origin.col_index)
		map[i][j]->x_space = (j - origin.col_index) * SPACE;
	else
		map[i][j]->x_space = 0;
}

t_point	***ft_copy_map(t_point ***map)
{
	int		i;
	int		j;
	t_point	***new_map;

	new_map = malloc((ft_struct_map_len(map) + 1) * sizeof(t_point **));
	i = 0;
	while (map[i])
	{
		new_map[i] = malloc((ft_struct_linelen(map[i]) + 1)
				* (sizeof(t_point *)));
		j = 0;
		while (map[i][j])
		{
			new_map[i][j] = ft_copy_point(map[i][j]);
			j++;
		}
		new_map[i][j] = NULL;
		i++;
	}
	new_map[i] = NULL;
	return (new_map);
}

t_point	*ft_copy_point(t_point *point)
{
	t_point	*new_point;

	new_point = malloc(sizeof(t_point));
	new_point->x = point->x;
	new_point->y = point->y;
	new_point->z = point->z;
	new_point->x_space = point->x_space;
	new_point->y_space = point->y_space;
	new_point->color = point->color;
	return (new_point);
}

int	ft_linelen(char **line)
{
	int	i;

	i = 0;
	if (!line)
		return (i);
	while (line[i])
		i++;
	return (i);
}
