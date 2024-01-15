/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_two.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:33:26 by vda-conc          #+#    #+#             */
/*   Updated: 2024/01/15 17:16:55 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

char	***ft_join_map(char ***old_map, char **new_line)
{
	char	***new_map;
	int		old_map_size;
	int		i;

	old_map_size = ft_maplen(old_map);
	new_map = malloc((old_map_size + 2) * sizeof(char **));
	if (!new_map)
		return (NULL);
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

t_point	***ft_convert_map(char ***map)
{
	int		i;
	int		j;
	t_point	***new_map;

	new_map = malloc((ft_maplen(map) + 1) * sizeof(t_point **));
	if (!new_map)
		return (NULL);
	i = 0;
	while (map[i])
	{
		new_map[i] = malloc((ft_linelen(map[i]) + 1) * (sizeof(t_point *)));
		if (!new_map[i])
			return (NULL);
		j = 0;
		while (map[i][j])
		{
			new_map[i][j] = ft_convert_point(j, i, map[i][j]);
			if (!new_map[i][j++])
				return (NULL);
		}
		new_map[i][j] = NULL;
		i++;
	}
	new_map[i] = NULL;
	return (new_map);
}

int	ft_find_coma(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			return (1);
		i++;
	}
	return (0);
}

int	ft_struct_map_len(t_point ***map)
{
	int	i;

	if (!map)
		return (0);
	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	ft_struct_linelen(t_point **line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i])
		i++;
	return (i);
}
