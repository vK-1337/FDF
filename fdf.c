/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:47:59 by vda-conc          #+#    #+#             */
/*   Updated: 2024/01/04 09:25:04 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int main(int ac, char **av)
{
	int fd;
	char **map;

	if (ac < 2)
		return (0);
	fd = open(av[1], O_RDONLY);
 	if (fd == -1)
    	return (write(2, "Invalid file\n", 14), 0);
	map = ft_create_map_from_file(fd);
	if (!map)
		return (close(fd), 0);
  ft_print_all_lines(map);
	// CREATE MAP FROM FILE
	// CHECK IF MAP IS VALID
	// FDF(MAP)
}
