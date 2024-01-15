/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:13:18 by vda-conc          #+#    #+#             */
/*   Updated: 2024/01/15 11:27:54 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_zoom_adjust(t_point ***map)
{
	int	i;
	int	j;
	int	mid_col;
	int	last_line;

	mid_col = ft_define_mid_col(map);
	last_line = ft_struct_map_len(map) - 1;
	while (map[last_line][mid_col]->y < 980)
	{
		i = 0;
		while (map[i])
		{
			j = 0;
			while (map[i][j])
			{
				map[i][j]->x *= 3;
				map[i][j]->x += (CENTER_X * 0.1);
				map[i][j]->y *= 3;
				map[i][j]->y += (CENTER_Y * 0.1);
				map[i][j++]->z *= 3;
			}
			i++;
		}
	}
	ft_center_for_parallel(map);
}

void	ft_zoom_in(t_hook_data *redraw)
{
	int	i;
	int	j;

	i = 0;
	while (redraw->map[i])
	{
		j = 0;
		while (redraw->map[i][j])
		{
			redraw->map[i][j]->x *= 1.1;
			redraw->map[i][j]->x -= (CENTER_X * 0.1);
			redraw->map[i][j]->y *= 1.1;
			redraw->map[i][j]->y -= (CENTER_Y * 0.1);
			redraw->map[i][j]->z *= 1.1;
			j++;
		}
		i++;
	}
}

void	ft_zoom_out(t_hook_data *redraw)
{
	int	i;
	int	j;

	i = 0;
	while (redraw->map[i])
	{
		j = 0;
		while (redraw->map[i][j])
		{
			redraw->map[i][j]->x *= 0.9;
			redraw->map[i][j]->x += (CENTER_X * 0.1);
			redraw->map[i][j]->y *= 0.9;
			redraw->map[i][j]->y += (CENTER_Y * 0.1);
			redraw->map[i][j]->z *= 0.9;
			j++;
		}
		i++;
	}
}
