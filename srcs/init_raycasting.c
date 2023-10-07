/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:43:22 by mamesser          #+#    #+#             */
/*   Updated: 2023/10/03 16:53:51 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_map_steps_ray_len(t_vars *vars)
{
	if (vars->ray->ray_dir_x < 0)
	{
		vars->ray->step_x = -1;
		vars->ray->sidedist_x = (vars->pl_pos_x - vars->ray->map_x)
			* vars->ray->deltadist_x;
	}
	else
	{
		vars->ray->step_x = 1;
		vars->ray->sidedist_x = (vars->ray->map_x + 1.0 - vars->pl_pos_x)
			* vars->ray->deltadist_x;
	}
	if (vars->ray->ray_dir_y < 0)
	{
		vars->ray->step_y = -1;
		vars->ray->sidedist_y = (vars->pl_pos_y - vars->ray->map_y)
			* vars->ray->deltadist_y;
	}
	else
	{
		vars->ray->step_y = 1;
		vars->ray->sidedist_y = (vars->ray->map_y + 1.0 - vars->pl_pos_y)
			* vars->ray->deltadist_y;
	}
}

void	calc_ray_step_len(t_vars *vars)
{
	vars->ray->deltadist_x = fabs(1 / vars->ray->ray_dir_x);
	vars->ray->deltadist_y = fabs(1 / vars->ray->ray_dir_y);
}

void	calc_ray_dir(t_vars *vars)
{
	vars->ray->camera_x = (2.0 * (double)vars->screen_x
			/ (double)vars->screen_width - 1.0);
	vars->ray->ray_dir_x = vars->ray->view_x
		+ vars->ray->plane_x * vars->ray->camera_x;
	vars->ray->ray_dir_y = vars->ray->view_y
		+ vars->ray->plane_y * vars->ray->camera_x;
}

void	init_raycast(t_vars *vars)
{
	vars->ray->side = 0;
	vars->ray->hit = 0;
	vars->ray->map_x = (int)vars->pl_pos_x;
	vars->ray->map_y = (int)vars->pl_pos_y;
	calc_ray_dir(vars);
	calc_ray_step_len(vars);
	init_map_steps_ray_len(vars);
}
