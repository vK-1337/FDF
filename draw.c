/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:00:15 by vda-conc          #+#    #+#             */
/*   Updated: 2024/01/15 16:49:31 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_point ***map, t_data *img)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((j < ft_struct_linelen(map[i])) && (map[i][j + 1]))
				bresenham(*map[i][j], *map[i][j + 1], img);
			if ((i < ft_struct_map_len(map) - 1) && map[i + 1][j])
				bresenham(*map[i][j], *map[i + 1][j], img);
			j++;
		}
		i++;
	}
}

void	draw_text(void *mlx_ptr, void *win_ptr, int y, char *text)
{
	mlx_string_put(mlx_ptr, win_ptr, 10, y, 0xFFFFFF, text);
}

void	ft_draw_commands(void *mlx_ptr, void *win_ptr)
{
	draw_text(mlx_ptr, win_ptr, 20, "X Rotation == X || Shift+X || Left Click");
	draw_text(mlx_ptr, win_ptr, 40, "Y Rotation == Y || Shift+Y || Left Click");
	draw_text(mlx_ptr, win_ptr, 60, "Z Rotation == Z || Shift+Z || Left Click");
	draw_text(mlx_ptr, win_ptr, 80, "Move == Arrows|| Left Click");
	draw_text(mlx_ptr, win_ptr, 100, "Zoom == Scroll");
	draw_text(mlx_ptr, win_ptr, 120, "Isometric == I");
	draw_text(mlx_ptr, win_ptr, 140, "Parallellic == P");
	draw_text(mlx_ptr, win_ptr, 160, "Restart Animation == R");
	draw_text(mlx_ptr, win_ptr, 180, "Exit == ESC");
}

void	bresenham(t_point point_one, t_point point_two, t_data *img)
{
	t_bres_data	bres_data;

	ft_assign_bres_data(&bres_data, point_one, point_two);
	while (bres_data.x1 != bres_data.x2 || bres_data.y1 != bres_data.y2)
	{
		bres_data.color = get_color(point_one.color, point_two.color,
				bres_data.ratio);
		my_mlx_pixel_put(img, bres_data.x1, bres_data.y1, bres_data.color);
		bres_data.err2 = 2 * bres_data.err;
		if (bres_data.err2 > -bres_data.dy)
		{
			bres_data.err -= bres_data.dy;
			bres_data.x1 += bres_data.sx;
		}
		if (bres_data.err2 < bres_data.dx)
		{
			bres_data.err += bres_data.dx;
			bres_data.y1 += bres_data.sy;
		}
		bres_data.ratio += bres_data.increment;
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
