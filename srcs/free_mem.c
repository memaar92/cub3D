/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 14:14:24 by mamesser          #+#    #+#             */
/*   Updated: 2023/10/06 16:09:04 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	free_wall_tex(t_vars *vars)
{
	if (vars->tex_no && vars->tex_no)
		mlx_destroy_image(vars->mlx, vars->tex_no->img);
	if (vars->tex_so && vars->tex_so)
		mlx_destroy_image(vars->mlx, vars->tex_so->img);
	if (vars->tex_we && vars->tex_we)
		mlx_destroy_image(vars->mlx, vars->tex_we->img);
	if (vars->tex_ea && vars->tex_ea)
		mlx_destroy_image(vars->mlx, vars->tex_ea->img);
	if (vars->tex_no)
		free(vars->tex_no);
	if (vars->tex_so)
		free(vars->tex_so);
	if (vars->tex_we)
		free(vars->tex_we);
	if (vars->tex_ea)
		free(vars->tex_ea);
}

void	free_images(t_vars	*vars)
{
	free_wall_tex(vars);
	if (vars->scr_buf && vars->scr_buf->img)
		mlx_destroy_image(vars->mlx, vars->scr_buf->img);
	if (vars->tex_floor && vars->tex_floor)
		mlx_destroy_image(vars->mlx, vars->tex_floor->img);
	if (vars->tex_ceil && vars->tex_ceil)
		mlx_destroy_image(vars->mlx, vars->tex_ceil->img);
	if (vars->weapon && vars->weapon)
		mlx_destroy_image(vars->mlx, vars->weapon->img);
	if (vars->cam_low && vars->cam_low)
		mlx_destroy_image(vars->mlx, vars->cam_low->img);
	if (vars->scr_buf)
		free(vars->scr_buf);
	if (vars->tex_floor)
		free(vars->tex_floor);
	if (vars->tex_ceil)
		free(vars->tex_ceil);
	if (vars->weapon)
		free(vars->weapon);
	if (vars->cam_low)
		free(vars->cam_low);
}

void	free_map(t_vars *vars, int **map)
{
	int	i;

	if (!map)
		return ;
	i = -1;
	while (++i < vars->array_cols + 1)
		free(map[i]);
	free(map);
}

void	free_all_mem(t_vars *vars)
{
	if (vars->map)
		free_map(vars, vars->map);
	if (vars->ray)
		free(vars->ray);
	if (vars->floor)
		free(vars->floor);
	if (vars->textures)
		free_mem(vars->textures);
	free_images(vars);
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
	free(vars);
}
