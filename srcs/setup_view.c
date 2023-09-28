/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_raycast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:28:30 by mamesser          #+#    #+#             */
/*   Updated: 2023/09/28 19:23:25 by mamesser         ###   ########.fr       */
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
