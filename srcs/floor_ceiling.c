/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:13:37 by mamesser          #+#    #+#             */
/*   Updated: 2023/10/05 14:39:38 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	calc_floor_params(t_vars *vars)
{
	vars->floor->ray_dir_x0 = vars->ray->view_x - vars->ray->plane_x;
	vars->floor->ray_dir_y0 = vars->ray->view_y - vars->ray->plane_y;
	vars->floor->ray_dir_x1 = vars->ray->view_x + vars->ray->plane_x;
	vars->floor->ray_dir_y1 = vars->ray->view_y + vars->ray->plane_y;
	vars->floor->dist_scr_ctre = vars->floor->scre_y - vars->screen_height / 2;
	vars->floor->cam_to_floor = vars->floor->cam_height / vars->floor->dist_scr_ctre;
	vars->floor->floor_step_x = vars->floor->cam_to_floor * (vars->floor->ray_dir_x1 - vars->floor->ray_dir_x0) / vars->screen_width;
	// vars->floor->floor_step_x = 0.5;
	vars->floor->floor_step_y = vars->floor->cam_to_floor * (vars->floor->ray_dir_y1 - vars->floor->ray_dir_y0) / vars->screen_width;
	// printf("step y: %f\n", vars->floor->floor_step_y);
	// if (vars->floor->floor_step_y == 0.0)
	// 	vars->floor->floor_step_y = 1.0;
	// printf("ray_dir_x1: %f, ray_dir_x0: %f\n", vars->floor->ray_dir_x1, vars->floor->ray_dir_x0);
	// printf("step x: %f\n", vars->floor->floor_step_x);
	// vars->floor->floor_x = vars->pl_pos_x + vars->floor->dist_scr_ctre * vars->floor->ray_dir_x0;
	vars->floor->floor_x = 0.0;
	vars->floor->floor_y = vars->pl_pos_y + vars->floor->dist_scr_ctre * vars->floor->ray_dir_y0;
}

int	get_floor_color(int tex_x_pos, int tex_y_pos, t_vars *vars)
{
	int	color;
	int	pos;

	// tex_y_pos = tex_y_pos & (128 - 1);
	pos = tex_y_pos * (vars->tex_no->line_size / 4) + tex_x_pos;
	color = (int)(vars->tex_floor->addr[pos]);
	return (color);
}

// int	get_ceiling_color(int tex_x_pos, int tex_y_pos, t_vars *vars)
// {
// 	int	color;
// 	int	pos;

// 	// tex_y_pos = tex_y_pos & (128 - 1);
// 	pos = tex_y_pos * (vars->tex_no->line_size / 4) + tex_x_pos;
// 	color = (int)(vars->tex_ceil->addr[pos]);
// 	return (color);
// }

void	draw_floor(t_vars *vars)
{
	int	color;
	
	vars->floor->scre_y = 0;
	vars->floor->cam_height = 0.5 * vars->screen_height;
	while (vars->floor->scre_y < vars->screen_height)
	{
		calc_floor_params(vars);
		vars->floor->scre_x = 0;
		while (vars->floor->scre_x < vars->screen_width)
		{
			vars->floor->cell_x = (int)vars->floor->floor_x;
			vars->floor->cell_y = (int)vars->floor->floor_y;
			// vars->floor->tex_x = (int)vars->floor->floor_x  & (vars->tex_w - 1);
			// vars->floor->tex_y = (int)vars->floor->floor_y  & (vars->tex_h - 1);
			vars->floor->tex_x = (int)(vars->tex_w * (vars->floor->floor_x - vars->floor->cell_x)) & (vars->tex_w - 1);
			vars->floor->tex_y = (int)(vars->tex_h * (vars->floor->floor_y - vars->floor->cell_y)) & (vars->tex_h - 1);
			// printf("step: %f\n", vars->floor->floor_step_y);
			// printf("floor y: %f\n, cell y: %d\n", vars->floor->floor_y, vars->floor->cell_y);
			// printf("step y: %f\n", vars->floor->floor_step_y);
			// printf("tex x: %d\n, tex y: %d\n", vars->floor->tex_x, vars->floor->tex_y);
			// printf("screen y: %d\n", vars->floor->scre_y);
			vars->floor->floor_x += vars->floor->floor_step_x;
			vars->floor->floor_y += vars->floor->floor_step_y;
			color = get_floor_color(vars->floor->tex_x, vars->floor->tex_y, vars);
			// color = 9031664;
			vars->scr_buf->addr[vars->floor->scre_y * (vars->scr_buf->line_size / 4) + vars->floor->scre_x] = color;
			color = 6958116;
			vars->scr_buf->addr[(vars->screen_height - vars->floor->scre_y - 1) * (vars->scr_buf->line_size / 4) + vars->floor->scre_x] = color;
			vars->floor->scre_x++;
		}
		vars->floor->scre_y++;
	}
}
