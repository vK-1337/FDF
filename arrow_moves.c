/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:12:40 by vda-conc          #+#    #+#             */
/*   Updated: 2024/01/15 16:49:59 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_move_down(t_point ***map, t_positions *positions)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (positions == NULL)
				map[i][j]->y += 10;
			else
				map[i][j]->y -= positions->old_y - positions->new_y;
			j++;
		}
		i++;
	}
}

void	ft_move_up(t_point ***map, t_positions *positions)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (positions == NULL)
				map[i][j]->y -= 10;
			else
				map[i][j]->y -= positions->old_y - positions->new_y;
			j++;
		}
		i++;
	}
}

void	ft_move_left(t_point ***map, t_positions *positions)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (positions == NULL)
				map[i][j]->x -= 10;
			else
				map[i][j]->x -= positions->old_x - positions->new_x;
			j++;
		}
		i++;
	}
}

void	ft_move_right(t_point ***map, t_positions *positions)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (positions == NULL)
				map[i][j]->x += 10;
			else
				map[i][j]->x -= positions->old_x - positions->new_x;
			j++;
		}
		i++;
	}
}

void	ft_arrow_moves(t_hook_data *data, int key)
{
	if (key == 65362)
		ft_move_up(data->map, NULL);
	if (key == 65364)
		ft_move_down(data->map, NULL);
	if (key == 65361)
		ft_move_left(data->map, NULL);
	if (key == 65363)
		ft_move_right(data->map, NULL);
}
