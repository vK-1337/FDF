/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:56:43 by vda-conc          #+#    #+#             */
/*   Updated: 2024/01/15 14:57:37 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_move_right_up(t_hook_data *data, t_positions *positions)
{
	ft_move_right(data->map, positions);
	ft_move_up(data->map, positions);
}

void	ft_move_right_down(t_hook_data *data, t_positions *positions)
{
	ft_move_right(data->map, positions);
	ft_move_down(data->map, positions);
}

void	ft_move_left_up(t_hook_data *data, t_positions *positions)
{
	ft_move_left(data->map, positions);
	ft_move_up(data->map, positions);
}

void	ft_move_left_down(t_hook_data *data, t_positions *positions)
{
	ft_move_left(data->map, positions);
	ft_move_down(data->map, positions);
}

void	ft_mouse_one(t_hook_data *data, t_positions *positions, int old_x,
		int old_y)
{
	if (data->mouse_x > old_x && data->mouse_y < old_y)
		ft_move_right_up(data, positions);
	else if (data->mouse_x > old_x && data->mouse_y > old_y)
		ft_move_right_down(data, positions);
	else if (data->mouse_x < old_x && data->mouse_y < old_y)
		ft_move_left_up(data, positions);
	else if (data->mouse_x < old_x && data->mouse_y > old_y)
		ft_move_left_down(data, positions);
	else if (data->mouse_x > old_x)
		ft_move_right(data->map, positions);
	else if (data->mouse_x < old_x)
		ft_move_left(data->map, positions);
	else if (data->mouse_y > old_y)
		ft_move_down(data->map, positions);
	else if (data->mouse_y < old_y)
		ft_move_up(data->map, positions);
}
