/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:38:46 by valmpani          #+#    #+#             */
/*   Updated: 2023/10/05 14:39:30 by mamesser         ###   ########.fr       */
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
	{
		free_mem(vars->textures);
		return (free(vars), 1);
	}
	vars->ray = ft_calloc(sizeof(t_ray), 1);
	if (!vars->ray)
	{
		free_mem(vars->textures);
		free(vars->floor);
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
	if (init_screen_buffer(vars))
		return (1);
	if (init_textures(vars))
		return (1);
	vars->torch = malloc(sizeof(t_img));
	if (!vars->torch)
		return (1);
	vars->torch->img = mlx_xpm_file_to_image(vars->mlx, "./textures/torch.xpm",
			&vars->torch->tex_w, &vars->torch->tex_h);
	if (!vars->torch->img)
		return (1);
	vars->torch->addr = (int *)mlx_get_data_addr(vars->torch->img, &vars->torch->bpp,
			&vars->torch->line_size, &vars->torch->endian);
	if (!vars->torch->addr)
		return (1);
	vars->tex_floor = malloc(sizeof(t_img));
	if (!vars->tex_floor)
		return (1);
	vars->tex_floor->img = mlx_xpm_file_to_image(vars->mlx, "./textures/floor.xpm",
			&vars->tex_floor->tex_w, &vars->tex_floor->tex_h);
	if (!vars->tex_floor->img)
		return (1);
	vars->tex_floor->addr = (int *)mlx_get_data_addr(vars->tex_floor->img, &vars->tex_floor->bpp,
			&vars->tex_floor->line_size, &vars->tex_floor->endian);
	if (!vars->tex_floor->addr)
		return (1);
		
	// vars->tex_ceil = malloc(sizeof(t_img));
	// if (!vars->tex_ceil)
	// 	return (1);
	// vars->vars->tex_ceil->img = mlx_xpm_file_to_image(vars->mlx, "./textures/floor.xpm",
	// 		&vars->tex_floor->tex_w, &vars->tex_floor->tex_h);
	// if (!vars->tex_floor->img)
	// 	return (1);
	// vars->tex_floor->addr = (int *)mlx_get_data_addr(vars->tex_floor->img, &vars->tex_floor->bpp,
	// 		&vars->tex_floor->line_size, &vars->tex_floor->endian);
	// if (!vars->tex_floor->addr)
	// 	return (1);
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

t_vars	*init_vars(void)
{
	t_vars	*vars;

	vars = ft_calloc(sizeof(t_vars), 1);
	if (!vars)
		return (NULL);
	if (allocate_mem(vars))
		return (NULL);
	ft_bzero(vars, 0);
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
