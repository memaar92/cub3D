/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:54:59 by mamesser          #+#    #+#             */
/*   Updated: 2023/09/26 11:11:05 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	ft_close(t_vars *vars)
{
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
	exit(0);
}

int	get_pixel_color(int x, int y, t_vars *vars)
{
	int	color;
	int pos;


	pos = x * 4 + 4 * vars->size_line * y;
	color = (int)(vars->text_addr[pos]);

	// mlx_put_image_to_window(vars->mlx, vars->win, vars->test_texture, 0, 0);

	// printf("test: %c\n", (char)&(vars->text_addr)[0]);
	return (color);
}

void	draw_wall(t_vars *vars)
{
	int	color;
	int	y;

	vars->ray->draw_start = (500 / 2) - (vars->ray->line_height / 2);
	if (vars->ray->draw_start < 0)
		vars->ray->draw_start = 0;
	vars->ray->draw_end = (500 / 2) + (vars->ray->line_height / 2);
	if (vars->ray->draw_end >= 500)
		vars->ray->draw_end = 500 - 1;
	y = vars->ray->draw_start;
	while (y <= vars->ray->draw_end)
	{
		color = get_pixel_color(vars->ray->x, 0, vars);
		mlx_pixel_put(vars->mlx, vars->win, vars->ray->x, y, color);
		y++;
	}
}

void	calc_line_height(t_ray *ray)
{
	if(ray->side == 0)
		ray->perpWallDist = (ray->sideDistX - ray->deltaDistX);
	else
		ray->perpWallDist = (ray->sideDistY - ray->deltaDistY);
	ray->line_height = (int)(10000 / ray->perpWallDist); // there is probably a better formula taking into account distance from player to camera plane (cf permadi tutorial)
}

void	run_dda(t_vars *vars, int map[500][500])
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
		// mlx_pixel_put(vars->mlx, vars->win, mapX, mapY, 16777215);
		if (map[vars->ray->mapY][vars->ray->mapX] > 0)
			vars->ray->hit = 1;
	}
}


void	init_raycast(t_ray *ray)
{
	ray->x = 0;

	ray->playerX = 200;
	ray->playerY = 250;
	ray->side = 0; 	//init var side to track which side of the wall has been hit (e.g. 0 --> N or S; 1 --> E or W ??)

	// set viewing direction (--> west)
	ray->viewX = -1;
	ray->viewY = 0;

	// set camera plane position
	ray->planeX = 0; // --> this determines how wide the FOV is (together with viewX or viewY respectively)
	ray->planeY = 0.66;  // because viewX != 0 and viewY == 0; otherwise would not be perpendicular
}


void	init_casting(t_vars *vars)
{
	vars->array_cols = 500; // for testing
	vars->ray->hit = 0; // init hit flag
	vars->ray->mapX = (int)vars->ray->playerX; // set the position within the array we are currently at; for every ray initialized with the starting position
	vars->ray->mapY = (int)vars->ray->playerY; // set the position within the array we are currently at; for every ray initialized with the starting position
	// calc ray position and direction
	vars->ray->cameraX = ((double)2 * (double)vars->ray->x / (double)vars->array_cols) - (double)1; // for traversing the camera plane with increasing x / basically casting a new ray for every new x
	vars->ray->rayDirX = vars->ray->viewX + vars->ray->planeX * vars->ray->cameraX;
	vars->ray->rayDirY = vars->ray->viewY + vars->ray->planeY * vars->ray->cameraX;
	// size of increments from one x-side/y-side to the next x-side/y-side; simplified pythagoras and making the assumption that only the *ratio* between deltaDistX and deltaDistY matters for the DDA
	vars->ray->deltaDistX = 1 / vars->ray->rayDirX; // make sure to not divide by zero?
	if (vars->ray->deltaDistX < 0)
		vars->ray->deltaDistX *= -1;
	vars->ray->deltaDistY = 1 / vars->ray->rayDirY; // make sure to not divide by zero?
	if (vars->ray->deltaDistY < 0)
		vars->ray->deltaDistY *= -1;
	// calc matrix step (int) and length of ray from the initial position to the next side/line of the raster; required for DDA
	if (vars->ray->rayDirX < 0)
	{
		vars->ray->stepX = -1;
		vars->ray->sideDistX = (vars->ray->playerX - vars->ray->mapX) * vars->ray->deltaDistX;
	}
	else
	{
		vars->ray->stepX = 1;
		vars->ray->sideDistX = (vars->ray->mapX + 1.0 - vars->ray->playerX) * vars->ray->deltaDistX;
	}
	if (vars->ray->rayDirY < 0)
	{
		vars->ray->stepY = -1;
		vars->ray->sideDistY = (vars->ray->playerY - vars->ray->mapY) * vars->ray->deltaDistY;
	}
	else
	{
		vars->ray->stepY = 1;
		vars->ray->sideDistY = (vars->ray->mapY + 1.0 - vars->ray->playerY) * vars->ray->deltaDistY;
	}
}


int	cast_rays(int map[500][500], t_vars *vars)
{
	while (vars->ray->x < vars->array_cols) // probably terminating condition to be redefined
	{
		// go through each column x
		while (vars->ray->x < vars->array_cols)
		{
			init_casting(vars);
			// apply DDA (Digital Differential Analyzer; alternatively: Bresenham)
			// for "moving" along the ray and checking for intersections/hits
			run_dda(vars, map);
			// calculate the perpendicular distance of the ray (from the camera plane not the player) to the wall
			// why exactly does this calculation work?
			calc_line_height(vars->ray);
			// drawing the related vertical line
			draw_wall(vars);
			vars->ray->x++;
		}
	}
	return (0);
}

int	create_test_map(t_vars *vars)
{
	int	map[500][500];
	// int	y = 0;
	// int	x = 0;
	int fd;
	int i = -1;
	int j = -1;
	char	*line;

	// read test map
	fd = open("./testmap500x500.txt", O_RDONLY);
	while (++i < 500)
	{
		j = -1;
		line = get_next_line(fd);
		if (!line)
			return (1);
		while (line[++j])
		{
			if (line[j] == '1')
			{
				map[i][j] = 1;
				// mlx_pixel_put(vars->mlx, vars->win, j, i, 65280);
			}
			else if (line[j] == '0')
				map[i][j] = 0;
			else if (line[j] == 'P')
				map[i][j] = 9;
		}
		free(line);
	}

	int	w;
	int	h;
	int	bpp;
	int	endian;

	vars->test_texture = mlx_xpm_file_to_image(vars->mlx, "./textures/test_texture2.xpm", &w, &h);
	vars->text_addr = (int *)mlx_get_data_addr(vars->test_texture, &bpp, &vars->size_line, &endian);

	cast_rays(map, vars);
	return (0);
}


int	ft_render(t_vars *vars)
{
	init_raycast(vars->ray); // maybe not needed and values are partly set before
	create_test_map(vars); // includes the ray_cast
	return (0);
}


int	main(void)
{
	t_vars	vars;
	// create a 2D int array (this will later be created from the parsed .cub map)
	
	// init mlx and creating the display/window
	vars.mlx = mlx_init();
	if (!vars.mlx)
		return (1);
	vars.win = mlx_new_window(vars.mlx, 500, 500, "Title");
	if (!vars.win)
		return (free(vars.mlx), 1);
	// mlx_pixel_put(vars.mlx, vars.win, 100, 100, 16777215);
	// mlx_pixel_put(vars.mlx, vars.win, 101, 100, 16777215);
	// mlx_pixel_put(vars.mlx, vars.win, 99, 100, 16777215);
	mlx_hook(vars.win, 12, 1L << 15, ft_render, &vars);
	mlx_hook(vars.win, 17, 0L, ft_close, &vars);
	mlx_loop(vars.mlx);
	
}
