/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:03:15 by vda-conc          #+#    #+#             */
/*   Updated: 2024/01/13 18:23:59 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void ft_points_spacing(t_point ***map)
{
  int i;
  int j;
  t_origin origin;

  origin = ft_define_origin(map);
  i = 0;
  while (map[i])
  {
    j = 0;
    while (map[i][j])
    {
      if (i < origin.row_index)
        map[i][j]->y_space = (i - origin.row_index) * SPACE;
      else if (i > origin.row_index)
        map[i][j]->y_space = (i - origin.row_index) * SPACE;
      else
        map[i][j]->y_space = 0;
      if (j < origin.col_index)
        map[i][j]->x_space = (j - origin.col_index) * SPACE;
      else if (j > origin.col_index)
        map[i][j]->x_space = (j - origin.col_index) * SPACE;
      else
        map[i][j]->x_space = 0;
      j++;
    }
    i++;
  }
}
