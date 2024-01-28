/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:16:59 by vda-conc          #+#    #+#             */
/*   Updated: 2024/01/27 18:44:02 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_render(t_hook_data *data)
{
	mlx_destroy_image(data->mlx, data->img->img);
	data->img->img = mlx_new_image(data->mlx, 1920, 1080);
	draw_line(data->map, data->img);
	if (data->berserk_map == 1 && data->any_key_pressed == 0)
		ft_berserk_animation(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img, 0, 0);
	// ft_draw_commands(data->mlx, data->mlx_win);
	return (0);
}

void	ft_set_hooks(t_hook_data *data)
{
	mlx_hook(data->mlx_win, KeyPress, KeyPressMask, ft_handle_key_pressed,
		data);
	mlx_hook(data->mlx_win, KeyRelease, KeyReleaseMask, ft_handle_key_released,
		data);
	mlx_hook(data->mlx_win, ButtonPress, ButtonPressMask, ft_handle_mouse_press,
		data);
	mlx_hook(data->mlx_win, ButtonRelease, ButtonReleaseMask,
		ft_handle_mouse_release, data);
	mlx_hook(data->mlx_win, MotionNotify, PointerMotionMask,
		ft_handle_mouse_motion, data);
	mlx_hook(data->mlx_win, 17, 0, ft_close_win, data);
	mlx_loop_hook(data->mlx, &ft_render, data);
}
