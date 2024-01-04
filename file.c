/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:20:25 by vda-conc          #+#    #+#             */
/*   Updated: 2024/01/04 12:26:40 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int ft_valid_file(char *file_name)
{
  int name_len;

  name_len = ft_strlen(file_name);

  if (file_name[name_len - 4] != '.')
    return (0);
  else if (file_name[name_len - 3] != 'f')
    return (0);
  else if (file_name[name_len - 2] != 'd')
    return (0);
  else if (file_name[name_len - 1] != 'f')
    return (0);
  return (1);
}
