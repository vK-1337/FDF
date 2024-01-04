/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:47:59 by vda-conc          #+#    #+#             */
/*   Updated: 2024/01/04 20:45:03 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char **av)
{
	int		fd;
	char	**map;

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

int	ft_fdf(char **map)
{
	void	*mlx;
  void *mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	ft_grid(map, &img);
  mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
void ft_grid(char **map, t_data *img)
{
  int x;
  int y;
  int space;
  int i;
  int j;
  int k;

  space = 50;
  x = 300;
  y = 500;
  i = 0;
  while (map[i])
  {
    x = 300;
    j = 0;
    while (map[i][j])
    {
      k = x;
      while (k < x + space)
      {
        my_mlx_pixel_put(img, k++, y, 0x00FF0000);
      }
      k = y;
      while (k < y + space && map[i + 1])
      {
        my_mlx_pixel_put(img, x, k++, 0x00FF0000);
      }
      x += space;
      j++;
    }
    y += space;
    i++;
  }
}
