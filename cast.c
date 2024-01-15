/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:16:13 by vda-conc          #+#    #+#             */
/*   Updated: 2024/01/15 14:33:22 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_cast_point(t_point *point, int angle, int x_space, int y_space)
{
	double		rad;
	double		cos_theta;
	double		sin_theta;
	t_spaces	spaces;

	rad = (angle * M_PI) / 180.0;
	cos_theta = cos(rad);
	sin_theta = sin(rad);
	spaces.x_space = x_space;
	spaces.y_space = y_space;
	ft_rotate_z(point, sin_theta, cos_theta, &spaces);
	ft_rotate_x(point, sin_theta, cos_theta);
}

void	ft_cast_whole_map(t_point ***map, int angle, int space)
{
	int	i;
	int	j;
	int	x_space;
	int	y_space;

	i = 0;
	y_space = map[0][0]->y_space;
	while (map[i])
	{
		j = 0;
		x_space = map[i][0]->x_space;
		while (map[i][j])
		{
			ft_cast_point(map[i][j], angle, x_space, y_space);
			x_space += space;
			j++;
		}
		y_space += space;
		i++;
	}
}
