/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:38:46 by valmpani          #+#    #+#             */
/*   Updated: 2023/10/07 11:43:40 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	allocate_mem(t_vars *vars)
{
	vars->textures = ft_calloc(5, sizeof(char *));
	if (!vars->textures)
		return (free(vars), 1);
	vars->floor = ft_calloc(sizeof(t_floor), 1);
	if (!vars->floor)
		return (free_mem(vars->textures), free(vars), 1);
	vars->ray = ft_calloc(sizeof(t_ray), 1);
	if (!vars->ray)
		return (free_mem(vars->textures), free(vars->floor), free(vars), 1);
	vars->item = ft_calloc(sizeof(t_item), 1);
	if (!vars->item)
	{
		free_mem(vars->textures);
		free(vars->floor);
		free(vars->ray);
		return (free(vars), 1);
	}
	return (0);
}

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

int	init_tex_and_scr_buf(t_vars *vars)
{
	if (alloc_tex_mem(vars))
		return (1);
	if (init_screen_buffer(vars))
		return (1);
	if (init_wall_textures(vars))
		return (1);
	if (init_floor_ceil_textures(vars))
		return (1);
	if (init_hand_item_textures(vars))
		return (1);
	return (0);
}

int	init_mlx(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (1);
	vars->win = mlx_new_window(vars->mlx, vars->screen_width,
			vars->screen_height, "cub3D");
	if (!vars->win)
		return (1);
	return (0);
}

t_vars	*init_vars(int argc)
{
	t_vars	*vars;

	vars = ft_calloc(sizeof(t_vars), 1);
	if (!vars)
		return (NULL);
	ft_bzero(vars, sizeof(t_vars));
	if (allocate_mem(vars))
		return (NULL);
	if (argc == 3)
		vars->bonus = 1;
	vars->textures[SO] = NULL;
	vars->textures[NO] = NULL;
	vars->textures[WE] = NULL;
	vars->textures[EA] = NULL;
	vars->textures[4] = NULL;
	vars->pov_dir = -1;
	vars->screen_width = 1280;
	vars->screen_height = 720;
	set_floor_ceil(&vars);
	return (vars);
}
