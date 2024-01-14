/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:47:59 by vda-conc          #+#    #+#             */
/*   Updated: 2024/01/14 20:23:58 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char **av)
{
	int		fd;
	char	***map;
	t_point	***struct_map;

	if (ac < 2)
		return (0);
	fd = open(av[1], O_RDONLY);
	if (fd == -1 || !ft_valid_file(av[1]))
		return (write(2, "Invalid file\n", 14), 0);
	map = ft_create_map_from_file(fd);
	if (!map)
		return (close(fd), 0);
	struct_map = ft_convert_map(map);
	ft_free_map(map);
	ft_points_spacing(struct_map);
	ft_fdf(struct_map);
	ft_free_struct_map(struct_map);
	return (0);
}

void ft_zoom_adjust(t_point ***map)
{
  int i;
  int j;
  int mid_col;
  int last_line;

  mid_col = ft_define_mid_col(map);
  last_line = ft_struct_map_len(map) - 1;

  while(map[last_line][mid_col]->y < 980)
  {
    i = 0;
    while (map[i])
    {
      j = 0;
      while (map[i][j])
      {
        map[i][j]->x *= 3;
        map[i][j]->x += (CENTER_X * 0.1);
        map[i][j]->y *= 3;
        map[i][j]->y += (CENTER_Y * 0.1);
        map[i][j]->z *= 3;
        j++;
      }
      i++;
    }
  }
  ft_center_for_parallel(map);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
int	handle_key_released(int key, t_hook_data *data)
{
	if (key == 65505)
		data->shift_pressed = 0;
	return (0);
}

int	handle_key_pressed(int key, t_hook_data *data)
{
	if (key == 65307)
		ft_close_win(data);
	if (key == 65505)
		data->shift_pressed = 1;
	if (key == 'x')
	{
		if (data->shift_pressed)
			ft_rotate_map_x(data->map, -0.05);
		else
			ft_rotate_map_x(data->map, 0.05);
	}
	if (key == 'y')
	{
		if (data->shift_pressed)
			ft_rotate_map_y(data->map, -0.05);
		else
			ft_rotate_map_y(data->map, 0.05);
	}
	if (key == 'z')
	{
		if (data->shift_pressed)
			ft_rotate_map_z(data->map, -0.05);
		else
			ft_rotate_map_z(data->map, 0.05);
	}
	if (key == 'p')
	{
    ft_free_struct_map(data->map);
		data->map = ft_copy_map(data->original_map);
    ft_zoom_adjust(data->map);
	}
	if (key == 'i')
	{
    ft_free_struct_map(data->map);
		data->map = ft_copy_map(data->original_map);
		ft_cast_whole_map(data->map, 45, SPACE);
    ft_center_whole_map(data->map);
	}
	if (key == 65362)
		ft_move_up(data->map, NULL);
	if (key == 65364)
		ft_move_down(data->map, NULL);
	if (key == 65361)
		ft_move_left(data->map, NULL);
	if (key == 65363)
		ft_move_right(data->map, NULL);
	return (0);
}

void	ft_zoom_in(t_hook_data *redraw)
{
	int	i;
	int	j;

	i = 0;
	while (redraw->map[i])
	{
		j = 0;
		while (redraw->map[i][j])
		{
			redraw->map[i][j]->x *= 1.1;
			redraw->map[i][j]->x -= (CENTER_X * 0.1);
			redraw->map[i][j]->y *= 1.1;
			redraw->map[i][j]->y -= (CENTER_Y * 0.1);
			redraw->map[i][j]->z *= 1.1;
			j++;
		}
		i++;
	}
}
void	ft_zoom_out(t_hook_data *redraw)
{
	int	i;
	int	j;

	i = 0;
	while (redraw->map[i])
	{
		j = 0;
		while (redraw->map[i][j])
		{
			redraw->map[i][j]->x *= 0.9;
			redraw->map[i][j]->x += (CENTER_X * 0.1);
			redraw->map[i][j]->y *= 0.9;
			redraw->map[i][j]->y += (CENTER_Y * 0.1);
			redraw->map[i][j]->z *= 0.9;
			j++;
		}
		i++;
	}
}

void	ft_move_down(t_point ***map, t_positions *positions)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (positions == NULL)
				map[i][j]->y += 10;
			else
				map[i][j]->y -= positions->old_y - positions->new_y;
			j++;
		}
		i++;
	}
}

void	ft_move_up(t_point ***map, t_positions *positions)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (positions == NULL)
				map[i][j]->y -= 10;
			else
				map[i][j]->y -= positions->old_y - positions->new_y;
			j++;
		}
		i++;
	}
}

void	ft_move_left(t_point ***map, t_positions *positions)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (positions == NULL)
				map[i][j]->x -= 10;
			else
				map[i][j]->x -= positions->old_x - positions->new_x;
			j++;
		}
		i++;
	}
}

void	ft_move_right(t_point ***map, t_positions *positions)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (positions == NULL)
				map[i][j]->x += 10;
			else
				map[i][j]->x -= positions->old_x - positions->new_x;
			j++;
		}
		i++;
	}
}
int	ft_render(t_hook_data *redraw)
{
	mlx_destroy_image(redraw->mlx, redraw->img->img);
	redraw->img->img = mlx_new_image(redraw->mlx, 1920, 1080);
	draw_line(redraw->map, redraw->img);
	mlx_put_image_to_window(redraw->mlx, redraw->mlx_win, redraw->img->img, 0,
		0);
	ft_draw_commands(redraw->mlx, redraw->mlx_win);
	return (0);
}
int	handle_mouse_press(int button, int x, int y, t_hook_data *data)
{
	if (button == 1)
	{
		data->mouse_x = x;
		data->mouse_y = y;
		data->mouse_one_pressed = 1;
	}
	if (button == 3)
	{
		data->mouse_x = x;
		data->mouse_y = y;
		data->mouse_two_pressed = 1;
	}
	if (button == 4)
		ft_zoom_in(data);
	if (button == 5)
		ft_zoom_out(data);
	return (0);
}

int	handle_mouse_release(int button, int x __attribute__((unused)),
		int y __attribute__((unused)), t_hook_data *data)
{
	if (button == 1)
		data->mouse_one_pressed = 0;
	if (button == 3)
		data->mouse_two_pressed = 0;
	return (0);
}

int	handle_mouse_motion(int x, int y, t_hook_data *data)
{
	int			old_x;
	int			old_y;
	t_positions	positions;

	if (data->mouse_one_pressed)
	{
		old_x = data->mouse_x;
		old_y = data->mouse_y;
		data->mouse_x = x;
		data->mouse_y = y;
		positions.old_x = old_x;
		positions.old_y = old_y;
		positions.new_x = data->mouse_x;
		positions.new_y = data->mouse_y;
		if (data->mouse_x > old_x && data->mouse_y < old_y)
		{
			ft_move_right(data->map, &positions);
			ft_move_up(data->map, &positions);
		}
		else if (data->mouse_x > old_x && data->mouse_y > old_y)
		{
			ft_move_right(data->map, &positions);
			ft_move_down(data->map, &positions);
		}
		else if (data->mouse_x < old_x && data->mouse_y < old_y)
		{
			ft_move_left(data->map, &positions);
			ft_move_up(data->map, &positions);
		}
		else if (data->mouse_x < old_x && data->mouse_y > old_y)
		{
			ft_move_left(data->map, &positions);
			ft_move_down(data->map, &positions);
		}
		else if (data->mouse_x > old_x)
			ft_move_right(data->map, &positions);
		else if (data->mouse_x < old_x)
			ft_move_left(data->map, &positions);
		else if (data->mouse_y > old_y)
			ft_move_down(data->map, &positions);
		else if (data->mouse_y < old_y)
			ft_move_up(data->map, &positions);
	}
	if (data->mouse_two_pressed)
	{
		old_x = data->mouse_x;
		old_y = data->mouse_y;
		data->mouse_x = x;
		data->mouse_y = y;
		positions.old_x = old_x;
		positions.old_y = old_y;
		positions.new_x = data->mouse_x;
		positions.new_y = data->mouse_y;
		if (data->mouse_x > old_x && data->mouse_y < old_y)
		{
			ft_rotate_map_x(data->map, 0.025);
			ft_rotate_map_y(data->map, -0.025);
		}
		else if (data->mouse_x > old_x && data->mouse_y > old_y)
		{
			ft_rotate_map_x(data->map, -0.025);
			ft_rotate_map_y(data->map, -0.025);
		}
		else if (data->mouse_x < old_x && data->mouse_y < old_y)
		{
			ft_rotate_map_x(data->map, 0.025);
			ft_rotate_map_y(data->map, 0.025);
		}
		else if (data->mouse_x < old_x && data->mouse_y > old_y)
		{
			ft_rotate_map_x(data->map, -0.025);
			ft_rotate_map_y(data->map, 0.025);
		}
		else if (data->mouse_x > old_x)
			ft_rotate_map_y(data->map, -0.025);
		else if (data->mouse_x < old_x)
			ft_rotate_map_y(data->map, 0.025);
		else if (data->mouse_y > old_y)
			ft_rotate_map_x(data->map, -0.025);
		else if (data->mouse_y < old_y)
			ft_rotate_map_x(data->map, 0.025);
	}
	return (0);
}
void	ft_rotate_map_z(t_point ***map, double angle)
{
	int		i;
	int		j;
	double	old_x;
	double	old_y;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			old_x = map[i][j]->x - CENTER_X;
			old_y = map[i][j]->y - CENTER_Y;
			map[i][j]->x = old_x * cos(angle) + old_y * (-sin(angle));
			map[i][j]->y = old_x * sin(angle) + old_y * cos(angle);
			map[i][j]->x += CENTER_X;
			map[i][j]->y += CENTER_Y;
			j++;
		}
		i++;
	}
}

void	ft_rotate_map_y(t_point ***map, double angle)
{
	int		i;
	int		j;
	double	old_x;
	double	old_z;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			old_x = map[i][j]->x - CENTER_X;
			old_z = map[i][j]->z;
			map[i][j]->x = old_x * cos(angle) + old_z * sin(angle);
			map[i][j]->z = old_x * (-sin(angle)) + old_z * cos(angle);
			map[i][j]->x += CENTER_X;
			j++;
		}
		i++;
	}
}

void	ft_rotate_map_x(t_point ***map, double angle)
{
	int		i;
	int		j;
	double	old_y;
	double	old_z;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			old_y = map[i][j]->y - CENTER_Y;
			old_z = map[i][j]->z;
			map[i][j]->y = old_y * cos(angle) + old_z * (-sin(angle));
			map[i][j]->z = old_y * sin(angle) + old_z * cos(angle);
			map[i][j]->y += CENTER_Y;
			j++;
		}
		i++;
	}
}

int	ft_fdf(t_point ***map)
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
	hook_data.original_map = ft_copy_map(map);
	ft_cast_whole_map(map, 45, SPACE);
	ft_center_whole_map(map);
	draw_line(map, &img);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	hook_data.map = map;
	hook_data.img = &img;
	hook_data.mlx = mlx;
	hook_data.mlx_win = mlx_win;
	hook_data.mouse_one_pressed = 0;
	hook_data.mouse_two_pressed = 0;
	hook_data.shift_pressed = 0;
	mlx_hook(mlx_win, KeyPress, KeyPressMask, handle_key_pressed, &hook_data);
	mlx_hook(mlx_win, KeyRelease, KeyReleaseMask, handle_key_released,
		&hook_data);
	mlx_hook(mlx_win, ButtonPress, ButtonPressMask, handle_mouse_press,
		&hook_data);
	mlx_hook(mlx_win, ButtonRelease, ButtonReleaseMask, handle_mouse_release,
		&hook_data);
	mlx_hook(mlx_win, MotionNotify, PointerMotionMask, handle_mouse_motion,
		&hook_data);
	mlx_hook(mlx_win, 17, 0, ft_close_win, &hook_data);
	mlx_loop_hook(mlx, &ft_render, &hook_data);
	mlx_loop(mlx);
	return (0);
}

t_point	***ft_copy_map(t_point ***map)
{
	int		i;
	int		j;
	t_point	***new_map;

	new_map = malloc((ft_struct_map_len(map) + 1) * sizeof(t_point **));
	i = 0;
	while (map[i])
	{
		new_map[i] = malloc((ft_struct_linelen(map[i]) + 1)
				* (sizeof(t_point *)));
		j = 0;
		while (map[i][j])
		{
			new_map[i][j] = ft_copy_point(map[i][j]);
			j++;
		}
		new_map[i][j] = NULL;
		i++;
	}
	new_map[i] = NULL;
	return (new_map);
}

t_point	*ft_copy_point(t_point *point)
{
	t_point	*new_point;

	new_point = malloc(sizeof(t_point));
	new_point->x = point->x;
	new_point->y = point->y;
	new_point->z = point->z;
	new_point->x_space = point->x_space;
	new_point->y_space = point->y_space;
	new_point->color = point->color;
	return (new_point);
}

int	ft_close_win(void *params)
{
	t_hook_data	*data;

	data = (t_hook_data *)params;
	mlx_destroy_image(data->mlx, data->img->img);
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	ft_free_struct_map(data->map);
	exit(0);
	return (0);
}

void	ft_center_whole_map(t_point ***map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			map[i][j]->x += CENTER_X;
			map[i][j]->y += CENTER_Y;
			j++;
		}
		i++;
	}
}

void ft_center_for_parallel(t_point ***map)
{
  int i;
  int j;
  int x_movement;
  int y_movement;
  t_origin middle_pos;
  t_point middle_point;

  middle_pos = ft_define_origin(map);
  middle_point = *map[middle_pos.row_index][middle_pos.col_index];
  if (middle_point.y > 540)
    y_movement = -100;
  else
    y_movement = 100;
  if (middle_point.x > 960)
    x_movement = -100;
  else
    x_movement = 100;
  while (map[middle_pos.row_index][middle_pos.col_index]->x >= 960)
  {
    i = 0;
    while (map[i])
    {
      j = 0;
      while (map[i][j])
      {
        map[i][j]->x += x_movement;
        j++;
      }
      i++;
    }
  }
  while (map[middle_pos.row_index][middle_pos.col_index]->y >= 540)
  {
    i = 0;
    while (map[i])
    {
      j = 0;
      while (map[i][j])
      {
        map[i][j]->y += y_movement;
        j++;
      }
      i++;
    }
  }
}

void	ft_print_struct_map(t_point ***struct_map)
{
	int	i;
	int	j;

	i = 0;
	while (struct_map[i])
	{
		j = 0;
		while (struct_map[i][j])
		{
			printf("x = %f, y = %f, z = %f, color = %ld\n", struct_map[i][j]->x,
				struct_map[i][j]->y, struct_map[i][j]->z,
				struct_map[i][j]->color);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	ft_rotate_z(t_point *point, double sin_theta, double cos_theta,
		int x_space, int y_space)
{
	double	new_x;
	double	new_y;

	new_x = ((point->x + (x_space)) * cos_theta) - ((point->y + (y_space))
			* sin_theta);
	new_y = ((point->x + (x_space)) * sin_theta) + ((point->y + (y_space))
			* cos_theta);
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

void	ft_cast_point(t_point *point, int angle, int x_space, int y_space)
{
	double	rad;
	double	cos_theta;
	double	sin_theta;

	rad = (angle * M_PI) / 180.0;
	cos_theta = cos(rad);
	sin_theta = sin(rad);
	ft_rotate_z(point, sin_theta, cos_theta, x_space, y_space);
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

void	draw_text(void *mlx_ptr, void *win_ptr, int x, int y, int color,
		char *text)
{
	mlx_string_put(mlx_ptr, win_ptr, x, y, color, text);
}

void	ft_draw_commands(void *mlx_ptr, void *win_ptr)
{
	draw_text(mlx_ptr, win_ptr, 10, 20, 0xFFFFFF, "X Rotation == X || Shift + X || Right Click");
	draw_text(mlx_ptr, win_ptr, 10, 40, 0xFFFFFF, "Y Rotation == Y || Shift + Y || Right Click");
	draw_text(mlx_ptr, win_ptr, 10, 60, 0xFFFFFF, "Z Rotation == Z || Shift + Z || Right Click");
	draw_text(mlx_ptr, win_ptr, 10, 80, 0xFFFFFF, "Move == Arrows || Left Click");
	draw_text(mlx_ptr, win_ptr, 10, 100, 0xFFFFFF, "Zoom == Scroll");
	draw_text(mlx_ptr, win_ptr, 10, 120, 0xFFFFFF, "Isometric == I");
  draw_text(mlx_ptr, win_ptr, 10, 140, 0xFFFFFF, "Parallellic == P");
  draw_text(mlx_ptr, win_ptr, 10, 160, 0xFFFFFF, "Restart Animation == R");
	draw_text(mlx_ptr, win_ptr, 10, 180, 0xFFFFFF, "Exit == ESC");
}

void	bresenham(t_point point_one, t_point point_two, t_data *img)
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		err2;
	double	distance;
	double	ratio;
	double	increment;
	int		color;
	int		x1;
	int		y1;
	int		x2;
	int		y2;

	x1 = round(point_one.x);
	y1 = round(point_one.y);
	x2 = round(point_two.x);
	y2 = round(point_two.y);
	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	sx = x1 < x2 ? 1 : -1;
	sy = y1 < y2 ? 1 : -1;
	err = dx - dy;
	distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	increment = 1.0 / distance;
	ratio = 0;
	while (x1 != x2 || y1 != y2)
	{
		color = get_color(point_one.color, point_two.color, ratio);
		my_mlx_pixel_put(img, x1, y1, color);
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
		ratio += increment;
	}
}

int	get_color(int start_color, int end_color, double ratio)
{
	t_colors	colors;

	colors.start_red = (start_color >> 16) & 0xFF;
	colors.start_green = (start_color >> 8) & 0xFF;
	colors.start_blue = start_color & 0xFF;
	colors.end_red = (end_color >> 16) & 0xFF;
	colors.end_green = (end_color >> 8) & 0xFF;
	colors.end_blue = end_color & 0xFF;
	colors.red = interpolate(colors.start_red, colors.end_red, ratio);
	colors.green = interpolate(colors.start_green, colors.end_green, ratio);
	colors.blue = interpolate(colors.start_blue, colors.end_blue, ratio);
	return ((colors.red << 16) | (colors.green << 8) | colors.blue);
}

int	interpolate(int start, int end, double ratio)
{
	return (int)(start + (end - start) * ratio);
}
