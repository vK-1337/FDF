/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:13:54 by vda-conc          #+#    #+#             */
/*   Updated: 2024/01/04 09:23:36 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// int	ft_check_map_validity(int fd)
// {

// }

char	**ft_create_map_from_file(int fd)
{
	char	**map;
	char	*line;
	int		i;

	map = NULL;
	i = 0;
	line = get_next_line(fd);
	if (line)
	{
		while (line)
		{
			map = ft_join_map_lines(map, line);
			if (!map)
				return (ft_free_memory(map), free(line), NULL);
			line = get_next_line(fd);
			if (line == NULL)
				break;
		}
	}
	else
		return (NULL);
	return (map);
}

char	**ft_join_map_lines(char **map, char *new_line)
{
	char **new_map;
	int i;

	if (!new_line)
		return (NULL);
	new_map = malloc((ft_maplen(map) + 2) * sizeof(char *));
	if (!new_map)
		return (NULL);
	i = 0;
	if (!map)
		new_map[i++] = new_line;
	else
	{
		while (map[i])
		{
			new_map[i] = map[i];
			i++;
		}
		new_map[i++] = new_line;
	}
	new_map[i] = NULL;
	free(map);
	return (new_map);
}

int ft_maplen(char **map)
{
	int i;

	i = 0;
	if (!map)
		return (i);
	while (map[i])
		i++;
	return (i);
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
