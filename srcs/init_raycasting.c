/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:43:22 by mamesser          #+#    #+#             */
/*   Updated: 2023/10/03 15:51:44 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_map_steps_ray_len(t_vars *vars)
{
	if (vars->ray->rayDirX < 0)
	{
		vars->ray->stepX = -1;
		vars->ray->sideDistX = (vars->pl_pos_x - vars->ray->mapX)
			* vars->ray->deltaDistX;
	}
	else
	{
		vars->ray->stepX = 1;
		vars->ray->sideDistX = (vars->ray->mapX + 1.0 - vars->pl_pos_x)
			* vars->ray->deltaDistX;
	}
	if (vars->ray->rayDirY < 0)
	{
		vars->ray->stepY = -1;
		vars->ray->sideDistY = (vars->pl_pos_y - vars->ray->mapY)
			* vars->ray->deltaDistY;
	}
	else
	{
		vars->ray->stepY = 1;
		vars->ray->sideDistY = (vars->ray->mapY + 1.0 - vars->pl_pos_y)
			* vars->ray->deltaDistY;
	}
}

void	calc_ray_step_len(t_vars *vars)
{
	vars->ray->deltaDistX = fabs(1 / vars->ray->rayDirX);
	vars->ray->deltaDistY = fabs(1 / vars->ray->rayDirY);
}

void	calc_ray_dir(t_vars *vars)
{
	vars->ray->cameraX = (2.0 * (double)vars->screen_x
			/ (double)vars->screen_width - 1.0);
	vars->ray->rayDirX = vars->ray->viewX
		+ vars->ray->planeX * vars->ray->cameraX;
	vars->ray->rayDirY = vars->ray->viewY
		+ vars->ray->planeY * vars->ray->cameraX;
}

void	init_raycast(t_vars *vars)
{
	vars->ray->side = 0;
	vars->ray->hit = 0;
	vars->ray->mapX = (int)vars->pl_pos_x;
	vars->ray->mapY = (int)vars->pl_pos_y;
	calc_ray_dir(vars);
	calc_ray_step_len(vars);
	init_map_steps_ray_len(vars);
}
