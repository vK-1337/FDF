/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   berserk.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:04:40 by vda-conc          #+#    #+#             */
/*   Updated: 2024/01/27 18:50:09 by vda-conc         ###   ########.fr       */
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
  static int j = 1;

	if (data->r_key_pressed == 1)
  {
		i = 0;
    j = 1;
  }
	if (i == 0)
		ft_parallel_projection(data);
	if (i < 39)
		ft_rotate_map_z(data->map, -0.04);
	else if (i < 50)
		ft_zoom_out(data);
  else if (i < 79)
  {
    ft_change_color(data, j);
    j++;
  }
	else if (i)
		ft_rotate_map_y(data->map, 0.01);
	if (i < 1000000000000)
		i++;
  usleep(2000);
}

void ft_change_color(t_hook_data *data, int call_count)
{
  int start_color = 0x0001FE09;
  int end_color = 0xe40808;
  float ratio = (float)call_count / 30;
  for (int y = 0; data->map[y]; y++)
  {
    for (int x = 0; data->map[y][x]; x++)
    {
      if (data->map[y][x]->z == 0)
      {
        data->map[y][x]->color = 0x00000000;
        continue;
      }
      float start_red = (start_color >> 16) & 0xFF;
      float start_green = (start_color >> 8) & 0xFF;
      float start_blue = start_color & 0xFF;
      float end_red = (end_color >> 16) & 0xFF;
      float end_green = (end_color >> 8) & 0xFF;
      float end_blue = end_color & 0xFF;
      int new_red = (int)(start_red * (1 - ratio) + end_red * ratio);
      int new_green = (int)(start_green * (1 - ratio) + end_green * ratio);
      int new_blue = (int)(start_blue * (1 - ratio) + end_blue * ratio);
      new_red = new_red < 0 ? 0 : new_red > 255 ? 255 : new_red;
      new_green = new_green < 0 ? 0 : new_green > 255 ? 255 : new_green;
      new_blue = new_blue < 0 ? 0 : new_blue > 255 ? 255 : new_blue;
      int new_color = (new_red << 16) | (new_green << 8) | new_blue;
      data->map[y][x]->color = new_color;
    }
  }
}