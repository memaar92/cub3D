/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_raycast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpanis@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:28:30 by mamesser          #+#    #+#             */
/*   Updated: 2023/09/27 12:00:52 by valmpani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	set_camera_plane(t_vars *vars)
{
	if (vars->pov_dir == EA || vars->pov_dir == WE)
	{
		vars->ray->planeX = 0.0; // --> this determines how wide the FOV is (together with viewX or viewY respectively)
		vars->ray->planeY = 0.66;  // because viewX != 0 and viewY == 0; otherwise would not be perpendicular
	}
	else
	{
		vars->ray->planeX = 0.66;
		vars->ray->planeY = 0.0;
	}
}

void	set_viewing_direction(t_vars *vars)
{
	if (vars->pov_dir == NO)
	{
		vars->ray->viewX = 0;
		vars->ray->viewY = -1;
	}
	else if (vars->pov_dir == SO)
	{
		vars->ray->viewX = 0;
		vars->ray->viewY = 1;
	}
	else if (vars->pov_dir == WE)
	{
		vars->ray->viewX = -1;
		vars->ray->viewY = 0;
	}
	else if (vars->pov_dir == EA)
	{
		vars->ray->viewX = 1;
		vars->ray->viewY = 0;
	}
}

void	setup_raycast(t_vars *vars)
{
	vars->ray->x = 0; // set starting column; probably independent of array. This is where the screen starts
		
	vars->ray->playerX = vars->pl_pos_x; // this can be removed after aligning on coordinate system
	vars->ray->playerY = vars->pl_pos_y; // this can be removed after aligning on coordinate system
	
	// set viewing direction
	set_viewing_direction(vars);
	
	// set camera plane position
	set_camera_plane(vars);
}
