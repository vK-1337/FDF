/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:47:59 by vda-conc          #+#    #+#             */
/*   Updated: 2024/01/08 19:51:07 by vda-conc         ###   ########.fr       */
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
  ft_cast_whole_map(map, 45);
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
    i++;
  }
}

void ft_rotate_z(t_point *point, int angle)
{
  point->x = point->x * cos(angle) - point->y * sin(angle);
  point->y = point->x * sin(angle) + point->y * cos(angle);
}

void ft_rotate_x(t_point *point, int angle)
{
  point->y = point->x * cos(angle) - point->y * sin(angle);
}
void ft_cast_point(t_point *point, int angle)
{
  ft_rotate_z(point, angle);
  ft_rotate_x(point, angle);
}

void ft_cast_whole_map(t_point ***map, int angle)
{
  int i;
  int j;

  i = 0;
  while (map[i])
  {
    j = 0;
    while (map[i][j])
    {
      ft_cast_point(map[i][j], angle);
      j++;
    }
    i++;
  }
}

void	draw_line(t_point ***map, t_data *img)
{
	int	i;
	int	j;
	int	x;
  double x1;
  double y1;
  double x2;
  double y2;
  double x3;
  double y3;
  double x1_tan;
  double y1_tan;
  double x2_tan;
  double y2_tan;
  double x3_tan;
  double y3_tan;
	int	y;
	int	space;

	i = 0;
	space = 50;
	y = -500;
	while (map[i])
	{
		x = 800;
		j = 0;
		while (map[i][j])
		{
      if (j < 17 && i < 10)
      {
        x1 = ft_first_rot_x(x, y);
        y1 = ft_first_rot_y(x, y);
        //
        x2 = ft_first_rot_x(x + space, y);
        y2 = ft_first_rot_y(x + space, y);
        //
        x3 = ft_first_rot_x(x, y + space);
        y3 = ft_first_rot_y(x, y + space);
        // //
        x1_tan = ft_cast_point(map[i][j], 45);
        y1_tan = ft_arc_tan_y(x1, y1, ft_atoi(map[i][j]));
        //
        x2_tan = ft_arc_tan_x(x2);
        if (j == 19)
          y2_tan = ft_arc_tan_y(x2, y2, ft_atoi(map[i][j]));
        else
          y2_tan = ft_arc_tan_y(x2, y2, ft_atoi(map[i][j + 1]));
        x3_tan = ft_arc_tan_x(x3);
        if (i == 18)
          y3_tan = ft_arc_tan_y(x3, y3, ft_atoi(map[i][j]));
        else
          y3_tan = ft_arc_tan_y(x3, y3, ft_atoi(map[i + 1][j]));
        //
      }
			if ((j < ft_linelen(map[i])) && (map[i][j + 1]))
				bresenham(round(x1_tan), round(y1_tan), round(x2_tan), round(y2_tan), img);
			if ((i < ft_maplen(map) - 1) && map[i + 1][j])
				bresenham(round(x1_tan), round(y1_tan), round(x3_tan), round(y3_tan), img);
			x += space;
			j++;
		}
		y += space;
		i++;
	}
}

// if ((j < ft_linelen(map[i])) && (map[i][j + 1]))
// 				bresenham(round(x1_tan), round(y1_tan), round(x2_tan), round(y2_tan), img);
// if ((i < ft_maplen(map) - 1) && map[i + 1][j])
//   bresenham(round(x1_tan), round(y1_tan), round(x3_tan), round(y3_tan), img);

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
  x1 = (x * (sqrt(2) / 2)) - (y * (sqrt(2) / 2));
  printf("x1 = %f\n", x1);
  return (x1);
}

double ft_first_rot_y(int x, int y)
{
  double y1;
  y1 = (x * (sqrt(2) / 2)) + (y * (sqrt(2) / 2));
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
  (void)x;
  printf("Z => |%d|\n", z);
  y1 = (y * (sqrt(3)/3)) - (z * (sqrt(6)/3));
  return (y1);
}
