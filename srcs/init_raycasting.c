/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:43:22 by mamesser          #+#    #+#             */
/*   Updated: 2023/09/28 19:19:58 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_map_steps_ray_len(t_vars *vars)
{
	if (vars->ray->rayDirX < 0)
	{
		vars->ray->stepX = -1;
		vars->ray->sideDistX = (vars->pl_pos_x - vars->ray->mapX) * vars->ray->deltaDistX;
	}
	else
	{
		vars->ray->stepX = 1;
		vars->ray->sideDistX = (vars->ray->mapX + 1.0 - vars->pl_pos_x) * vars->ray->deltaDistX;
	}
	if (vars->ray->rayDirY < 0)
	{
		vars->ray->stepY = -1;
		vars->ray->sideDistY = (vars->pl_pos_y - vars->ray->mapY) * vars->ray->deltaDistY;
	}
	else
	{
		vars->ray->stepY = 1;
		vars->ray->sideDistY = (vars->ray->mapY + 1.0 - vars->pl_pos_y) * vars->ray->deltaDistY;
	}
}

void	calc_ray_step_len(t_vars *vars)
{
	vars->ray->deltaDistX = 1 / vars->ray->rayDirX; // make sure to not divide by zero?
	if (vars->ray->deltaDistX < 0)
		vars->ray->deltaDistX *= -1;
	vars->ray->deltaDistY = 1 / vars->ray->rayDirY; // make sure to not divide by zero?
	if (vars->ray->deltaDistY < 0)
		vars->ray->deltaDistY *= -1;
}

void	calc_ray_dir(t_vars *vars)
{
	vars->ray->cameraX = ((double)2 * (double)vars->screen_x / (double)vars->screen_width - (double)1); // for traversing the camera plane with increasing x / basically casting a new ray for every new x
	vars->ray->rayDirX = vars->ray->viewX + vars->ray->planeX * vars->ray->cameraX;
	vars->ray->rayDirY = vars->ray->viewY + vars->ray->planeY * vars->ray->cameraX;
}

void	init_raycast(t_vars *vars)
{
	// set basic variables; need to be reset in every loop
	vars->ray->side = 0; //init var side to track which side of the wall has been hit (e.g. 0 --> N or S; 1 --> E or W ??)
	vars->ray->hit = 0; // init hit flag
	vars->ray->mapX = (int)vars->pl_pos_x; // set the position within the array we are currently at; for every ray initialized with the player position
	vars->ray->mapY = (int)vars->pl_pos_y; // set the position within the array we are currently at; for every ray initialized with the player position
	
	// calc ray direction
	calc_ray_dir(vars);
	
	// size of increments from one x-side/y-side to the next x-side/y-side; simplified pythagoras and making the assumption that only the *ratio* between deltaDistX and deltaDistY matters for the DDA
	calc_ray_step_len(vars);
	
	// calc matrix step (int) and length of ray from the initial position to the next side/line of the raster; required for DDA
	init_map_steps_ray_len(vars);
}
