/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:47:59 by vda-conc          #+#    #+#             */
/*   Updated: 2024/01/07 15:39:17 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char **av)
{
	int		fd;
	char	***map;

	if (ac < 2)
		return (0);
	fd = open(av[1], O_RDONLY);
	if (fd == -1 || !ft_valid_file(av[1]))
		return (write(2, "Invalid file\n", 14), 0);
	map = ft_create_map_from_file(fd);
	if (!map)
		return (close(fd), 0);
	ft_fdf(map);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	ft_fdf(char ***map)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "FDF");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	draw_line(map, &img);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}

void	draw_line(char ***map, t_data *img)
{
	int	i;
	int	j;
	int	x;
  double x1;
  double y1;
  double x2;
  double y2;
  int x3;
  int y3;
  int x4;
  int y4;
	int	y;
	int	space;

	i = 0;
	space = 50;
	y = 300;
	while (map[i])
	{
		x = 800;
		j = 0;
		while (map[i][j])
		{
      x1 = (int)ft_first_rot_x(x, y);
      y1 = (int)ft_first_rot_y(x, y);
      x2 = (int)ft_first_rot_x(x + space, y);
      y2 = (int)ft_first_rot_y(x, y + space);
      x3 = (int)ft_arc_tan_x(x1);
      y3 = (int)ft_arc_tan_y(x2, y1, ft_atoi(map[i][j]));
      x4 = (int)ft_arc_tan_x(x2);
      y4 = (int)ft_arc_tan_y(x1, y2, ft_atoi(map[i][j]));
			if ((map[i + 1] && map[i + 1][j]) || i == 0)
				bresenham(x3, y3, x4, y3, img);
			if (map[i][j + 1])
				bresenham(x3, y3, x3, y4, img);
			x += space;
			j++;
		}
		y += space;
		i++;
	}
}

void	bresenham(int x1, int y1, int x2, int y2, t_data *img)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	err2;

	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	sx = x1 < x2 ? 1 : -1;
	sy = y1 < y2 ? 1 : -1;
	err = dx - dy;
	while (x1 != x2 || y1 != y2)
	{
		my_mlx_pixel_put(img, x1, y1, 0x00FF0000);
		err2 = 2 * err;
		if (err2 > -dy)
		{
			err -= dy;
			x1 += sx;
		}
		if (err2 < dx)
		{
			err += dx;
			y1 += sy;
		}
	}
}

double ft_first_rot_x(int x, int y)
{
  double x1;
  x1 = x * (sqrt(2) / 2) - y * (sqrt(2) / 2);
  printf("x1 = %f\n", x1);
  return (x1);
}

double ft_first_rot_y(int x, int y)
{
  double y1;
  y1 = x * (sqrt(2) / 2) + y * (sqrt(2) / 2);
  printf("y1 = %f\n", y1);
  return (y1);
}

double ft_arc_tan_x(double x)
{
  double x1;
  x1 = x;
  return (x1);
}

double ft_arc_tan_y(double x, double y, int z)
{
  double y1;
  y1 = x * 0 + ( y * sqrt(3)/3) - (z * sqrt(6)/3);
  return (y1);
}
