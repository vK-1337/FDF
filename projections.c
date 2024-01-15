/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:56:38 by vda-conc          #+#    #+#             */
/*   Updated: 2024/01/15 14:03:20 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_parallel_projection(t_hook_data *data)
{
	ft_free_struct_map(data->map);
	data->map = ft_copy_map(data->original_map);
	ft_zoom_adjust(data->map);
}

void	ft_iso_projection(t_hook_data *data)
{
	ft_free_struct_map(data->map);
	data->map = ft_copy_map(data->original_map);
	ft_cast_whole_map(data->map, 45, SPACE);
	ft_center_whole_map(data->map);
}
