/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 10:01:04 by valmpani          #+#    #+#             */
/*   Updated: 2023/09/23 10:01:07 by valmpani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	textures_not_filled(t_vars **vars)
{
	int	i;
	int	j;

	i = 0;
	while ((*vars)->textures[i])
		i++;
	if (i != 4)
		return (1);
	i = -1;
	while (++i < 2)
	{
		j = -1;
		while (++j < 3)
		{
			if ((*vars)->floor_ceiling[i][j] == -1)
				return (1);
		}
	}
	return (0);
}