/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:12:05 by vda-conc          #+#    #+#             */
/*   Updated: 2024/01/15 14:57:44 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_handle_mouse_press(int button, int x, int y, t_hook_data *data)
{
	if (button == 1)
	{
		data->mouse_x = x;
		data->mouse_y = y;
		data->mouse_one_pressed = 1;
	}
	if (button == 3)
	{
		data->mouse_x = x;
		data->mouse_y = y;
		data->mouse_two_pressed = 1;
	}
	if (button == 4)
		ft_zoom_in(data);
	if (button == 5)
		ft_zoom_out(data);
	return (0);
}

int	ft_handle_mouse_release(int button, int x, int y, t_hook_data *data)
{
	(void)x;
	(void)y;
	if (button == 1)
		data->mouse_one_pressed = 0;
	if (button == 3)
		data->mouse_two_pressed = 0;
	return (0);
}

void	ft_mouse_two(t_hook_data *data, int old_x, int old_y)
{
	if (data->mouse_x > old_x && data->mouse_y < old_y)
		ft_mouse_rotate_x_y(data, 0.025, -0.025);
	else if (data->mouse_x > old_x && data->mouse_y > old_y)
		ft_mouse_rotate_x_y(data, -0.025, -0.025);
	else if (data->mouse_x < old_x && data->mouse_y < old_y)
		ft_mouse_rotate_x_y(data, 0.025, 0.025);
	else if (data->mouse_x < old_x && data->mouse_y > old_y)
		ft_mouse_rotate_x_y(data, -0.025, 0.025);
	else if (data->mouse_x > old_x)
		ft_rotate_map_y(data->map, -0.025);
	else if (data->mouse_x < old_x)
		ft_rotate_map_y(data->map, 0.025);
	else if (data->mouse_y > old_y)
		ft_rotate_map_x(data->map, -0.025);
	else if (data->mouse_y < old_y)
		ft_rotate_map_x(data->map, 0.025);
}

void	ft_mouse_rotate_x_y(t_hook_data *data, double x_angle, double y_angle)
{
	ft_rotate_map_x(data->map, x_angle);
	ft_rotate_map_y(data->map, y_angle);
}

int	ft_handle_mouse_motion(int x, int y, t_hook_data *data)
{
	int			old_x;
	int			old_y;
	t_positions	positions;

	old_x = data->mouse_x;
	old_y = data->mouse_y;
	data->mouse_x = x;
	data->mouse_y = y;
	positions.old_x = old_x;
	positions.old_y = old_y;
	positions.new_x = data->mouse_x;
	positions.new_y = data->mouse_y;
	if (data->mouse_one_pressed)
		ft_mouse_one(data, &positions, old_x, old_y);
	if (data->mouse_two_pressed)
		ft_mouse_two(data, old_x, old_y);
	return (0);
}
