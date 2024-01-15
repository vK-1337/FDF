/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:09:37 by vda-conc          #+#    #+#             */
/*   Updated: 2024/01/15 16:48:09 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_handle_key_released(int key, t_hook_data *data)
{
	if (key == 65505)
		data->shift_pressed = 0;
	if (key == 'r')
		data->r_key_pressed = 0;
	return (0);
}

void	ft_handle_x(t_hook_data *data)
{
	if (data->shift_pressed)
		ft_rotate_map_x(data->map, -0.05);
	else
		ft_rotate_map_x(data->map, 0.05);
}

void	ft_handle_y(t_hook_data *data)
{
	if (data->shift_pressed)
		ft_rotate_map_y(data->map, -0.05);
	else
		ft_rotate_map_y(data->map, 0.05);
}

void	ft_handle_z(t_hook_data *data)
{
	if (data->shift_pressed)
		ft_rotate_map_z(data->map, -0.05);
	else
		ft_rotate_map_z(data->map, 0.05);
}

int	ft_handle_key_pressed(int key, t_hook_data *data)
{
	data->any_key_pressed = 1;
	if (key == 65307)
		ft_close_win(data);
	if (key == 65505)
		data->shift_pressed = 1;
	if (key == 'i')
		ft_iso_projection(data);
	if (key == 'p')
		ft_parallel_projection(data);
	if (key == 'r')
	{
		data->r_key_pressed = 1;
		data->any_key_pressed = 0;
	}
	if (key == 'x')
		ft_handle_x(data);
	if (key == 'y')
		ft_handle_y(data);
	if (key == 'z')
		ft_handle_z(data);
	if (key == 65362 || key == 65364 || key == 65361 || key == 65363)
		ft_arrow_moves(data, key);
	return (0);
}
