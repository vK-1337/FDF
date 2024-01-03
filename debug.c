/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:32:25 by vda-conc          #+#    #+#             */
/*   Updated: 2024/01/03 20:32:36 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void ft_print_all_lines(char ***lines_tab)
{
  int i;
  int j;

  i = 0;
  while (lines_tab[i])
  {
    j = 0;
    while (lines_tab[i][j])
    {
      printf("%s", lines_tab[i][j]);
      free(lines_tab[i][j++]);
    }
    i++;
  }
}
