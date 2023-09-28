/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:54:59 by mamesser          #+#    #+#             */
/*   Updated: 2023/09/28 19:46:12 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	get_pixel_color(int tex_x_pos, int tex_y_pos, t_vars *vars)
{
	int	color;
	int pos;
	
	pos = tex_y_pos * (vars->test_tex->line_size / 4) + tex_x_pos;
	color = (int)(vars->test_tex->addr[pos]);
	return (color);
}

void	put_text_on_buf_scr(t_vars *vars)
{
	int		color;
	double	tex_x_steps;
	double	tex_y_steps;
	int		tex_x_pos;
	int		tex_y_pos;
	double	tex_y_pos2;
	
	vars->ray->draw_start = (vars->screen_height / 2) - (vars->ray->line_height / 2);
	if (vars->ray->draw_start < 0)
		vars->ray->draw_start = 0;
	vars->ray->draw_end = (vars->screen_height / 2) + (vars->ray->line_height / 2);
	if (vars->ray->draw_end >= vars->screen_height)
		vars->ray->draw_end = vars->screen_height - 1;
	
	// currently not used; needed?
	// double wallX; 
	// if (vars->ray->side == 0)
	// 	wallX = vars->pl_pos_y + vars->ray->perpWallDist * vars->ray->rayDirY;
	// else
	// 	wallX = vars->pl_pos_x + vars->ray->perpWallDist * vars->ray->rayDirX;
	// wallX -= floor(wallX);

	// int texX = (int)(wallX * 128);
	// if ((vars->ray->side == 0 && vars->ray->rayDirX > 0) || (vars->ray->side == 1 && vars->ray->rayDirY < 0))
	// 	texX = 128 - texX - 1;

	tex_x_steps = 1.0 * vars->screen_x * vars->test_tex->tex_w / vars->ray->line_height;
	tex_x_pos = (int)tex_x_steps & (vars->test_tex->tex_w - 1);

	
	tex_y_steps = 1.0 * vars->test_tex->tex_h / vars->ray->line_height;
	tex_y_pos2 = (vars->ray->draw_start - vars->screen_height / 2 + vars->ray->line_height / 2) * tex_y_steps; // basically always 0.0?

	vars->screen_y = vars->ray->draw_start;
	while (vars->screen_y < vars->ray->draw_end)
	{
		tex_y_pos = (int)tex_y_pos2 & (vars->test_tex->tex_h - 1);
		tex_y_pos2 += tex_y_steps;
		color = get_pixel_color(tex_x_pos, tex_y_pos, vars);
		if (vars->ray->side == 1) 
			color = (color >> 1) & 8355711;
		// mlx_pixel_put(vars->mlx, vars->win, vars->screen_x, vars->screen_y, color); // should be printed to an image first; then entire image is put on window at the end
		vars->scr_buf->addr[vars->screen_y * (vars->scr_buf->line_size / 4) + vars->screen_x] = color;
		vars->screen_y++;
	}
}

void	calc_line_height(t_vars *vars)
{
	// why exactly does this calculation work?
	if(vars->ray->side == 0)
		vars->ray->perpWallDist = (vars->ray->sideDistX - vars->ray->deltaDistX);
	else
		vars->ray->perpWallDist = (vars->ray->sideDistY - vars->ray->deltaDistY);
	vars->ray->line_height = (int)((2 * vars->screen_height) / vars->ray->perpWallDist); // there is probably a better formula taking into account distance from player to camera plane (cf permadi tutorial)
}

void	run_dda(t_vars *vars)
{
	while (vars->ray->hit == 0)
	{
		if (vars->ray->sideDistX < vars->ray->sideDistY)
		{
			vars->ray->sideDistX += vars->ray->deltaDistX;
			vars->ray->mapX += vars->ray->stepX;
			vars->ray->side = 0; // to check which side has been hit (NS or EW?)
		}
		else
		{
			vars->ray->sideDistY += vars->ray->deltaDistY;
			vars->ray->mapY += vars->ray->stepY;
			vars->ray->side = 1; // to check which side has been hit (NS or EW?)
		}
		// for testing raycaster; draws single raycast towards hit point
		// mlx_pixel_put(vars->mlx, vars->win, vars->ray->mapX, vars->ray->mapY, 16777215);
		if (vars->map[vars->ray->mapX][vars->ray->mapY] == 1)
			vars->ray->hit = 1;
	}
}

int	cast_rays(t_vars *vars)
{
	// while (vars->screen_x < vars->array_cols) // probably terminating condition to be redefined
	// {
		// go through each column x
		while (vars->screen_x < vars->screen_width)
		{
			init_raycast(vars);
			
			// apply DDA (Digital Differential Analyzer; alternatively: Bresenham) for "moving" along the ray and checking for intersections/hits
			run_dda(vars);
			
			// calculate the perpendicular distance of the ray (from the camera plane not the player) to the wall
			calc_line_height(vars);
			
			// drawing the related vertical line to the screen buffer
			put_text_on_buf_scr(vars);
			
			vars->screen_x++;
		}
	// }
	return (0);
}

void print_2D_map_on_window(t_vars *vars) // just for testing; remove later
{
	int i = 0;
	while (i < (*vars).array_cols)
	{
		int	j = 0;
		while (j < (*vars).array_rows + 1)
		{
			if (vars->map[i][j] == 1)
				mlx_pixel_put(vars->mlx, vars->win, i, j, 65280);
			j++;
		}
		i++;
	}
}

void	draw_floor_ceiling(t_vars *vars)
{
	int	i;
	int j;
	int	floor_color;
	int	ceiling_color;

	i = 0;
	j = 0;
	floor_color = set_color(0, vars->floor_ceiling[0][0], vars->floor_ceiling[0][1], vars->floor_ceiling[0][2]);
	ceiling_color = set_color(0, vars->floor_ceiling[1][0], vars->floor_ceiling[1][1], vars->floor_ceiling[1][2]);
	while (i < vars->screen_width)
	{
		j = 0;
		while (j < vars->screen_height)
		{
			if (j <= vars->screen_height / 2)
				vars->scr_buf->addr[j * (vars->scr_buf->line_size / 4) + i] = ceiling_color;
			else
				vars->scr_buf->addr[j * (vars->scr_buf->line_size / 4) + i] = floor_color;
			j++;
		}
		i++;
	}
}

int	ft_render(t_vars *vars)
{
	draw_floor_ceiling(vars);
	
	//start rendering from the very left side of the screen
	vars->screen_x = 0;
	
	//setup viewpoint
	set_viewing_direction(vars);
	set_camera_plane(vars);
	
	// print_2D_map_on_window(vars); // for testing the raycasting
	
	// raycasting
	cast_rays(vars);

	// draw frame
	mlx_put_image_to_window(vars->mlx, vars->win, vars->scr_buf->img, 0, 0);
	return (0);
}
