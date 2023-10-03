/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:08:46 by mamesser          #+#    #+#             */
/*   Updated: 2023/10/03 16:53:51 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	dda_calc_sidedist_x(t_vars *vars)
{
	vars->ray->sidedist_x += vars->ray->deltadist_x;
	vars->ray->map_x += vars->ray->step_x;
	if (vars->ray->ray_dir_x > 0)
		vars->ray->wall_color = 0;
	else
		vars->ray->wall_color = 2;
	vars->ray->side = 0;
}

void	dda_calc_sidedist_y(t_vars *vars)
{
	vars->ray->sidedist_y += vars->ray->deltadist_y;
	vars->ray->map_y += vars->ray->step_y;
	if (vars->ray->ray_dir_y < 0)
		vars->ray->wall_color = 1;
	else
		vars->ray->wall_color = 3;
	vars->ray->side = 1;
}
