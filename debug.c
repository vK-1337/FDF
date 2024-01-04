/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:32:25 by vda-conc          #+#    #+#             */
/*   Updated: 2024/01/04 09:27:20 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void ft_print_all_lines(char **lines_tab)
{
  int i;

  i = 0;
  while (lines_tab[i])
  {
    {
      printf("%s", lines_tab[i]);
      free(lines_tab[i]);
    }
    i++;
  }
  free(lines_tab);
}
