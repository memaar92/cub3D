/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_view.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:28:30 by mamesser          #+#    #+#             */
/*   Updated: 2023/10/03 16:52:00 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	set_camera_plane(t_vars *vars)
{
	if (vars->pov_dir == EA || vars->pov_dir == WE)
	{
		vars->ray->plane_x = 0.0;
		vars->ray->plane_y = 0.66;
		if (vars->pov_dir == WE)
			vars->ray->plane_y = -0.66;
	}
	else
	{
		vars->ray->plane_x = 0.66;
		if (vars->pov_dir == SO)
			vars->ray->plane_x = -0.66;
		vars->ray->plane_y = 0.0;
	}
}

void	set_viewing_direction(t_vars *vars)
{
	if (vars->pov_dir == NO)
	{
		vars->ray->view_x = 0;
		vars->ray->view_y = -1;
	}
	else if (vars->pov_dir == SO)
	{
		vars->ray->view_x = 0;
		vars->ray->view_y = 1;
	}
	else if (vars->pov_dir == WE)
	{
		vars->ray->view_x = -1;
		vars->ray->view_y = 0;
	}
	else if (vars->pov_dir == EA)
	{
		vars->ray->view_x = 1;
		vars->ray->view_y = 0;
	}
}
