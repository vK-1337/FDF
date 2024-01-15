/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_rotations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:10:42 by vda-conc          #+#    #+#             */
/*   Updated: 2024/01/15 12:08:25 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	ft_rotate_map_z(t_point ***map, double angle)
{
	int		i;
	int		j;
	double	old_x;
	double	old_y;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			old_x = map[i][j]->x - CENTER_X;
			old_y = map[i][j]->y - CENTER_Y;
			map[i][j]->x = old_x * cos(angle) + old_y * (-sin(angle));
			map[i][j]->y = old_x * sin(angle) + old_y * cos(angle);
			map[i][j]->x += CENTER_X;
			map[i][j]->y += CENTER_Y;
			j++;
		}
		i++;
	}
}

void	ft_rotate_map_y(t_point ***map, double angle)
{
	int		i;
	int		j;
	double	old_x;
	double	old_z;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			old_x = map[i][j]->x - CENTER_X;
			old_z = map[i][j]->z;
			map[i][j]->x = old_x * cos(angle) + old_z * sin(angle);
			map[i][j]->z = old_x * (-sin(angle)) + old_z * cos(angle);
			map[i][j]->x += CENTER_X;
			j++;
		}
		i++;
	}
}

void	ft_rotate_map_x(t_point ***map, double angle)
{
	int		i;
	int		j;
	double	old_y;
	double	old_z;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			old_y = map[i][j]->y - CENTER_Y;
			old_z = map[i][j]->z;
			map[i][j]->y = old_y * cos(angle) + old_z * (-sin(angle));
			map[i][j]->z = old_y * sin(angle) + old_z * cos(angle);
			map[i][j]->y += CENTER_Y;
			j++;
		}
		i++;
	}
}
