/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:47:59 by vda-conc          #+#    #+#             */
/*   Updated: 2024/01/16 09:34:30 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char **av)
{
	int		fd;
	char	***map;
	t_point	***struct_map;

	if (ac < 2 || ac > 2)
		return (write(1, "Error\n => ./fdf [file_name.fdf]", 32), 0);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (write(2, "File not found\n", 16), 0);
	if (!ft_valid_file(av[1]))
		return (write(2, "Invalid file only .fdf accepted\n", 33), 0);
	map = ft_create_map_from_file(fd);
	if (!map)
		return (close(fd), 0);
	struct_map = ft_convert_map(map);
	if (!struct_map)
		return (close(fd), ft_free_map(map), 0);
	ft_free_map(map);
	ft_points_spacing(struct_map);
	if (ft_is_berserk_map(av[1]))
		ft_fdf(struct_map, 1);
	else
		ft_fdf(struct_map, 0);
	return (0);
}

int	ft_fdf(t_point ***map, int berserk_map)
{
	void		*mlx;
	void		*mlx_win;
	t_data		img;
	t_hook_data	hook_data;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "FDF");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	ft_color_map(map);
	hook_data.original_map = ft_copy_map(map);
	hook_data.img = &img;
	hook_data.berserk_map = berserk_map;
	ft_cast_whole_map(map, 45, SPACE);
	ft_center_whole_map(map);
	draw_line(map, &img);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	ft_assign_data(&hook_data, map, mlx, mlx_win);
	ft_set_hooks(&hook_data);
	mlx_loop(mlx);
	return (0);
}

void	ft_assign_data(t_hook_data *data, t_point ***map, void *mlx,
		void *mlx_win)
{
	data->map = map;
	data->mlx = mlx;
	data->mlx_win = mlx_win;
	data->mouse_one_pressed = 0;
	data->mouse_two_pressed = 0;
	data->shift_pressed = 0;
	data->r_key_pressed = 0;
	data->any_key_pressed = 0;
}
