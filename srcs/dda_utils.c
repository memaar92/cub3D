/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:08:46 by mamesser          #+#    #+#             */
/*   Updated: 2023/10/03 16:11:31 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	dda_calc_sidedist_x(t_vars *vars)
{
	vars->ray->sideDistX += vars->ray->deltaDistX;
	vars->ray->mapX += vars->ray->stepX;
	if (vars->ray->rayDirX > 0)
		vars->ray->wall_color = 0;
	else
		vars->ray->wall_color = 2;
	vars->ray->side = 0;
}

void	dda_calc_sidedist_y(t_vars *vars)
{
	vars->ray->sideDistY += vars->ray->deltaDistY;
	vars->ray->mapY += vars->ray->stepY;
	if (vars->ray->rayDirY < 0)
		vars->ray->wall_color = 1;
	else
		vars->ray->wall_color = 3;
	vars->ray->side = 1;
}
