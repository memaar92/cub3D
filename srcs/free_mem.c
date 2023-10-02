/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 14:14:24 by mamesser          #+#    #+#             */
/*   Updated: 2023/10/01 14:18:18 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	free_images(t_vars	*vars)
{
	if (vars->scr_buf->img)
		mlx_destroy_image(vars->mlx, vars->scr_buf->img);
	if (vars->tex_no)
		mlx_destroy_image(vars->mlx, vars->tex_no->img);
	if (vars->tex_so)
		mlx_destroy_image(vars->mlx, vars->tex_so->img);
	if (vars->tex_we)
		mlx_destroy_image(vars->mlx, vars->tex_we->img);
	if (vars->tex_ea)
		mlx_destroy_image(vars->mlx, vars->tex_ea->img);
	free(vars->scr_buf);
	free(vars->tex_no);
	free(vars->tex_so);
	free(vars->tex_we);
	free(vars->tex_ea);
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
