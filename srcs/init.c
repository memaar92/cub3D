/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpanis@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:38:46 by valmpani          #+#    #+#             */
/*   Updated: 2023/09/27 12:44:43 by valmpani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	set_floor_ceil(t_vars **vars)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 2)
	{
		j = -1;
		while (++j < 3)
			(*vars)->floor_ceiling[i][j] = -1;
	}
}

t_vars	*init_vars(void)
{
	t_vars	*vars;

	vars = ft_calloc(sizeof(t_vars), 1);
	if (!vars)
		return (NULL);
	(*vars).textures = ft_calloc(5, sizeof(char *));
	(*vars).map_pos = 0;
	if (!(*vars).textures)
		return (free(vars), NULL);
	(*vars).pov_dir = -1;
	(*vars).textures[SO] = NULL;
	(*vars).textures[NO] = NULL;
	(*vars).textures[WE] = NULL;
	(*vars).textures[EA] = NULL;
	(*vars).textures[4] = NULL;
	set_floor_ceil(&vars);
	return (vars);
}
