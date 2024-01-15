/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_four.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:36:37 by vda-conc          #+#    #+#             */
/*   Updated: 2024/01/15 17:37:03 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	ft_define_mid_col(t_point ***map)
{
	int	mid_col;
	int	map_line_len;

	map_line_len = ft_struct_linelen(map[0]);
	if (map_line_len % 2 == 0)
		mid_col = (map_line_len / 2) - 1;
	else
		mid_col = map_line_len / 2;
	return (mid_col);
}

int	ft_define_mid_row(t_point ***map)
{
	int	mid_row;
	int	map_len;

	map_len = ft_struct_map_len(map);
	if (map_len % 2 == 0)
		mid_row = (map_len / 2) - 1;
	else
		mid_row = map_len / 2;
	return (mid_row);
}

int	ft_maplen(char ***map)
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

int	ft_colored_map(t_point ***map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j]->color != 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	ft_color_map(t_point ***map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			map[i][j]->color = DEFAULT_COLOR;
			j++;
		}
		i++;
	}
}
