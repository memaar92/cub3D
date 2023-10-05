/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:13:37 by mamesser          #+#    #+#             */
/*   Updated: 2023/10/05 17:42:52 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	get_floor_color(int tex_x_pos, int tex_y_pos, t_vars *vars)
{
	int	color;
	int	pos;

	pos = tex_y_pos * (vars->tex_floor->line_size / 4) + tex_x_pos;
	color = (int)(vars->tex_floor->addr[pos]);
	return (color);
}

int	get_ceiling_color(int tex_x_pos, int tex_y_pos, t_vars *vars)
{
	int	color;
	int	pos;

	pos = tex_y_pos * (vars->tex_ceil->line_size / 4) + tex_x_pos;
	color = (int)(vars->tex_ceil->addr[pos]);
	return (color);
}

void	calc_floor_pos(t_vars *vars)
{
	if (vars->ray->side == 0 && vars->ray->ray_dir_x > 0)
	{
		vars->floor->wall_x = vars->ray->map_x;
		vars->floor->wall_y = vars->ray->map_y + vars->ray->wall_hit;
	}
	else if (vars->ray->side == 0 && vars->ray->ray_dir_x < 0)
	{
		vars->floor->wall_x = vars->ray->map_x + 1.0;
		vars->floor->wall_y = vars->ray->map_y + vars->ray->wall_hit;
	}
	else if (vars->ray->side == 1 && vars->ray->ray_dir_y > 0)
	{
		vars->floor->wall_x = vars->ray->map_x + vars->ray->wall_hit;
		vars->floor->wall_y = vars->ray->map_y;
	}
	else
	{
		vars->floor->wall_x = vars->ray->map_x + vars->ray->wall_hit;
		vars->floor->wall_y = vars->ray->map_y + 1.0;
	}
}

void	init_floor_vars(t_vars *vars)
{
	vars->floor->dist_wall = vars->ray->perpwalldist;
	vars->floor->dist_pl = 0.0;
	if (vars->ray->draw_end < 0)
		vars->ray->draw_end = vars->screen_height;
	vars->floor->y = vars->ray->draw_end + 1;
}

void	put_floor_ceil(t_vars *vars)
{
	int	color;

	color = 0;
	init_floor_vars(vars);
	calc_floor_pos(vars);
	while (vars->floor->y < vars->screen_height) // probably can be removed
	{
		vars->floor->current_dist = vars->screen_height
			/ (2.0 * vars->floor->y - vars->screen_height);
		vars->floor->weight = (vars->floor->current_dist - vars->floor->dist_pl)
			/ (vars->floor->dist_wall - vars->floor->dist_pl);
		vars->floor->cur_floor_x = vars->floor->weight * vars->floor->wall_x
			+ (1.0 - vars->floor->weight) * vars->pl_pos_x;
		vars->floor->cur_floor_y = vars->floor->weight * vars->floor->wall_y
			+ (1.0 - vars->floor->weight) * vars->pl_pos_y;
		vars->floor->tex_x = (int)(vars->floor->cur_floor_x * 256) % 256;
		vars->floor->tex_y = (int)(vars->floor->cur_floor_y * 256) % 256;
		color = get_floor_color(vars->floor->tex_x, vars->floor->tex_y, vars);
		vars->scr_buf->addr[vars->floor->y * (vars->scr_buf->line_size / 4)
			+ vars->screen_x] = color;
		color  = get_ceiling_color(vars->floor->tex_x,
			vars->floor->tex_y, vars); // testing ceiling
		color  = 78718; // testing ceiling
		vars->scr_buf->addr[(vars->screen_height - vars->floor->y)
			* (vars->scr_buf->line_size / 4) + vars->screen_x] = color;
		vars->floor->y++;
	}
}
