/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:07:48 by mamesser          #+#    #+#             */
/*   Updated: 2023/10/03 16:11:23 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	get_pixel_color(int tex_x_pos, int tex_y_pos, t_vars *vars)
{
	int	color;
	int	pos;

	pos = tex_y_pos * (vars->tex_no->line_size / 4) + tex_x_pos;
	if (vars->ray->wall_color == 0)
		color = (int)(vars->tex_we->addr[pos]);
	else if (vars->ray->wall_color == 1)
		color = (int)(vars->tex_no->addr[pos]);
	else if (vars->ray->wall_color == 2)
		color = (int)(vars->tex_ea->addr[pos]);
	else
		color = (int)(vars->tex_so->addr[pos]);
	return (color);
}

void	calc_line_height(t_vars *vars)
{
	if (vars->ray->side == 0)
		vars->ray->perpWallDist = (vars->ray->sideDistX
				- vars->ray->deltaDistX);
	else
		vars->ray->perpWallDist = (vars->ray->sideDistY
				- vars->ray->deltaDistY);
	vars->ray->line_height = (int)(vars->screen_height
			/ vars->ray->perpWallDist);
}

void	calc_vline_start_end(t_vars *vars)
{
	vars->ray->draw_start = (vars->screen_height / 2)
		- (vars->ray->line_height / 2);
	if (vars->ray->draw_start < 0)
		vars->ray->draw_start = 0;
	vars->ray->draw_end = (vars->screen_height / 2)
		+ (vars->ray->line_height / 2);
	if (vars->ray->draw_end >= vars->screen_height)
		vars->ray->draw_end = vars->screen_height - 1;
}

int	calc_texture_pos_x(t_vars *vars)
{
	double	wall_hit;
	int		tex_x_pos;

	if (vars->ray->side == 0)
	{
		wall_hit = vars->pl_pos_y + vars->ray->perpWallDist
			* vars->ray->rayDirY;
	}
	else
	{
		wall_hit = vars->pl_pos_x + vars->ray->perpWallDist
			* vars->ray->rayDirX;
	}
	wall_hit -= floor(wall_hit);
	tex_x_pos = (int)(wall_hit * (double)vars->tex_w);
	if ((vars->ray->side == 0 && vars->ray->rayDirX < 0)
		|| (vars->ray->side == 1 && vars->ray->rayDirY > 0))
	{
		tex_x_pos = 128 - tex_x_pos - 1;
	}
	return (tex_x_pos);
}
