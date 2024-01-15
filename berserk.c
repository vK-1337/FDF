/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   berserk.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:04:40 by vda-conc          #+#    #+#             */
/*   Updated: 2024/01/15 16:51:30 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_is_berserk_map(char *str)
{
	if (ft_strncmp(str, "berserk.fdf", 11) == 0 || ft_strncmp(str,
			"Berserk.fdf", 11) == 0)
		return (1);
	return (0);
}

void	ft_berserk_animation(t_hook_data *data)
{
	static long	i;

	if (data->r_key_pressed == 1)
		i = 0;
	if (i == 0)
		ft_parallel_projection(data);
	if (i < 39)
		ft_rotate_map_z(data->map, -0.04);
	else if (i < 45)
		ft_zoom_out(data);
	else if (i)
		ft_rotate_map_y(data->map, 0.03);
	if (i < 1000000000000)
		i++;
}
