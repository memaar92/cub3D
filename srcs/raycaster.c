/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:54:59 by mamesser          #+#    #+#             */
/*   Updated: 2023/09/27 12:28:58 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	get_pixel_color(int x, int y, t_vars *vars)
{
	int	color;
	int pos;
	

	pos = x * 4 + 4 * vars->size_line * y;
	color = (int)(vars->text_addr[pos]);
	return (color);
}

void	draw_wall(t_vars *vars)
{
	int	color;
	int	y;

	vars->ray->draw_start = (vars->screen_height / 2) - (vars->ray->line_height / 2);
	if (vars->ray->draw_start < 0)
		vars->ray->draw_start = 0;
	vars->ray->draw_end = (vars->screen_height / 2) + (vars->ray->line_height / 2);
	if (vars->ray->draw_end >= vars->screen_height)
		vars->ray->draw_end = vars->screen_height - 1;
	y = vars->ray->draw_start;
	while (y <= vars->ray->draw_end)
	{
		color = get_pixel_color(vars->ray->x, 0, vars); // needs to be adjusted; currently not working correctly as y is held constant
		mlx_pixel_put(vars->mlx, vars->win, vars->ray->x, y, color); // should be printed to an image first; then entire image is put on window at the end
		y++;
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
	// while (vars->ray->x < vars->array_cols) // probably terminating condition to be redefined
	// {
		// go through each column x
		while (vars->ray->x < vars->screen_width)
		{
			init_raycast(vars);
			
			// apply DDA (Digital Differential Analyzer; alternatively: Bresenham) for "moving" along the ray and checking for intersections/hits
			run_dda(vars);
			
			// calculate the perpendicular distance of the ray (from the camera plane not the player) to the wall
			calc_line_height(vars);
			
			// drawing the related vertical line
			draw_wall(vars);
			
			vars->ray->x++;
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

void	init_textures(t_vars *vars)
{
	int	w;
	int	h;
	int	bpp;
	int	endian;
	
	vars->test_texture = mlx_xpm_file_to_image(vars->mlx, "./textures/test_texture2.xpm", &w, &h);
	vars->text_addr = (int *)mlx_get_data_addr(vars->test_texture, &bpp, &vars->size_line, &endian);
}

int	ft_render(t_vars *vars)
{
	init_textures(vars); // for now just testing; needs to be replaced with textures provided + err checking; probably even want to do it earlier and not here
	setup_raycast(vars); // maybe not needed and values are partly set before
	// print_2D_map_on_window(vars); // for testing the raycasting
	cast_rays(vars);
	return (0);
}
