/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:02:16 by vda-conc          #+#    #+#             */
/*   Updated: 2024/01/15 14:33:07 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_rotate_z(t_point *point, double sin_theta, double cos_theta,
		t_spaces *spaces)
{
	double	new_x;
	double	new_y;

	new_x = ((point->x + (spaces->x_space)) * cos_theta) - ((point->y
				+ (spaces->y_space)) * sin_theta);
	new_y = ((point->x + (spaces->x_space)) * sin_theta) + ((point->y
				+ (spaces->y_space)) * cos_theta);
	point->x = new_x;
	point->y = new_y;
}

void	ft_rotate_x(t_point *point, double sin_theta, double cos_theta)
{
	double	new_y;
	double	new_z;

	new_y = (point->y * cos_theta) - ((point->z * 20) * sin_theta);
	new_z = (point->y * sin_theta) + ((point->z * 20) * cos_theta);
	point->y = new_y;
	point->z = new_z;
}

void	ft_rotate_y(t_point *point, double sin_theta, double cos_theta)
{
	double	new_x;
	double	new_z;

	new_x = (point->x * cos_theta) + ((point->z * 20) * sin_theta);
	new_z = (point->x * sin_theta) + ((point->z * 20) * cos_theta);
	point->x = new_x;
	point->z = new_z;
}
