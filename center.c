/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:19:47 by vda-conc          #+#    #+#             */
/*   Updated: 2024/01/15 12:44:00 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_center_whole_map(t_point ***map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			map[i][j]->x += CENTER_X;
			map[i][j]->y += CENTER_Y;
			j++;
		}
		i++;
	}
}

void	ft_center_for_parallel(t_point ***map)
{
	int			x_movement;
	int			y_movement;
	t_origin	middle_pos;
	t_point		*middle_point;

	middle_pos = ft_define_origin(map);
	middle_point = map[middle_pos.row_index][middle_pos.col_index];
	if (middle_point->y > 540)
		y_movement = -100;
	else
		y_movement = 100;
	if (middle_point->x > 960)
		x_movement = -100;
	else
		x_movement = 100;
	ft_center_x(map, middle_point, x_movement);
	ft_center_y(map, middle_point, y_movement);
}

void	ft_center_x(t_point ***map, t_point *middle_point, int x_movement)
{
	int	i;
	int	j;

	while (middle_point->x >= 960)
	{
		i = 0;
		while (map[i])
		{
			j = 0;
			while (map[i][j])
			{
				map[i][j]->x += x_movement;
				j++;
			}
			i++;
		}
	}
}

void	ft_center_y(t_point ***map, t_point *middle_point, int y_movement)
{
	int	i;
	int	j;

	while (middle_point->y >= 540)
	{
		i = 0;
		while (map[i])
		{
			j = 0;
			while (map[i][j])
			{
				map[i][j]->y += y_movement;
				j++;
			}
			i++;
		}
	}
}
