/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:47:59 by vda-conc          #+#    #+#             */
/*   Updated: 2024/01/09 16:32:58 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char **av)
{
	int		fd;
	char	***map;
  t_point ***struct_map;

	if (ac < 2)
		return (0);
	fd = open(av[1], O_RDONLY);
	if (fd == -1 || !ft_valid_file(av[1]))
		return (write(2, "Invalid file\n", 14), 0);
	map = ft_create_map_from_file(fd);
	if (!map)
		return (close(fd), 0);
  struct_map = ft_convert_map(map);
  ft_print_struct_map(struct_map);
  printf("\n\n");
	ft_fdf(struct_map);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

  if ( x > WIDTH || y > HEIGHT || x < 0 || y < 0)
    return;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	ft_fdf(t_point ***map)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "FDF");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
  ft_cast_whole_map(map, 45, 30);
	draw_line(map, &img);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}

void ft_print_struct_map(t_point ***struct_map)
{
  int i = 0, j;
  while (struct_map[i])
  {
    j = 0;
    while (struct_map[i][j])
    {
      printf("x = %f, y = %f, z = %f, color = %d\n", struct_map[i][j]->x, struct_map[i][j]->y, struct_map[i][j]->z, struct_map[i][j]->color);
      j++;
    }
    printf("\n");
    i++;
  }
}

void ft_rotate_z(t_point *point, double sin_theta, double cos_theta, int x_space, int y_space)
{
    double new_x = ((point->x + x_space) * cos_theta) - ((point->y + y_space) * sin_theta) + CENTER_X;
    double new_y = ((point->x + x_space) * sin_theta) + ((point->y + y_space) * cos_theta) + CENTER_Y;

    point->x = new_x;
    point->y = new_y;
}

void ft_rotate_x(t_point *point, double sin_theta, double cos_theta)
{

    double new_y;

    new_y = (point->y * cos_theta) - ((point->z) * sin_theta);
    point->y = new_y;
}
void ft_cast_point(t_point *point, int angle, int x_space, int y_space)
{
  double rad;
  double cos_theta;
  double sin_theta;

  rad = (angle * M_PI)/ 180.0;
  cos_theta = cos(rad);
  sin_theta = sin(rad);

  printf("x_space => %d, y_space => %d\n", x_space, y_space);

  ft_rotate_z(point, sin_theta, cos_theta, x_space, y_space);
  ft_rotate_x(point, sin_theta, cos_theta);
}


void ft_cast_whole_map(t_point ***map, int angle, int space)
{
  int i;
  int j;
  int x_space;
  int y_space;

  i = 0;
  y_space = 0;
  while (map[i])
  {
    j = 0;
    x_space = 0;
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
				bresenham(round(map[i][j]->x), round(map[i][j]->y), round(map[i][j + 1]->x), round(map[i][j + 1]->y), img);
			if ((i < ft_struct_map_len(map) - 1) && map[i + 1][j])
				bresenham(round(map[i][j]->x), round(map[i][j]->y), round(map[i + 1][j]->x), round(map[i + 1][j]->y), img);
			j++;
		}
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
