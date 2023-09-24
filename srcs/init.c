/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:38:46 by valmpani          #+#    #+#             */
/*   Updated: 2023/09/22 14:38:50 by valmpani         ###   ########.fr       */
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
	if (!(*vars).textures)
		return (free(vars), NULL);
	(*vars).orientation = -1;
	(*vars).textures[SO] = NULL;
	(*vars).textures[NO] = NULL;
	(*vars).textures[WE] = NULL;
	(*vars).textures[EA] = NULL;
	(*vars).textures[4] = NULL;
	set_floor_ceil(&vars);
	return (vars);
}