/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:01:35 by vda-conc          #+#    #+#             */
/*   Updated: 2024/01/15 12:21:39 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_color(int start_color, int end_color, double ratio)
{
	t_colors	colors;

	colors.start_red = (start_color >> 16) & 0xFF;
	colors.start_green = (start_color >> 8) & 0xFF;
	colors.start_blue = start_color & 0xFF;
	colors.end_red = (end_color >> 16) & 0xFF;
	colors.end_green = (end_color >> 8) & 0xFF;
	colors.end_blue = end_color & 0xFF;
	colors.red = interpolate(colors.start_red, colors.end_red, ratio);
	colors.green = interpolate(colors.start_green, colors.end_green, ratio);
	colors.blue = interpolate(colors.start_blue, colors.end_blue, ratio);
	return ((colors.red << 16) | (colors.green << 8) | colors.blue);
}

int	interpolate(int start, int end, double ratio)
{
	return ((int)(start + (end - start) * ratio));
}

int	ft_point_lesser(int point_one, int point_two)
{
	if (point_one < point_two)
		return (1);
	return (-1);
}

void	ft_assign_bres_data(t_bres_data *bres_data, t_point point_one,
		t_point point_two)
{
	bres_data->x1 = round(point_one.x);
	bres_data->y1 = round(point_one.y);
	bres_data->x2 = round(point_two.x);
	bres_data->y2 = round(point_two.y);
	bres_data->dx = abs(bres_data->x2 - bres_data->x1);
	bres_data->dy = abs(bres_data->y2 - bres_data->y1);
	bres_data->sx = ft_point_lesser(bres_data->x1, bres_data->x2);
	bres_data->sy = ft_point_lesser(bres_data->y1, bres_data->y2);
	bres_data->err = bres_data->dx - bres_data->dy;
	bres_data->distance = sqrt(pow(bres_data->x2 - bres_data->x1, 2)
			+ pow(bres_data->y2 - bres_data->y1, 2));
	bres_data->increment = 1.0 / bres_data->distance;
	bres_data->ratio = 0;
}
