/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:54:59 by mamesser          #+#    #+#             */
/*   Updated: 2023/09/23 14:38:09 by mamesser         ###   ########.fr       */
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

int	cast_rays(int map[500][500], t_vars *vars)
{
	int		x;
	int		side;
	double	playerX;
	double	playerY;
	double	viewX;
	double	viewY;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	planeX;
	double	planeY;
	// double	perpWallDist;
	int		hit;
	int		stepX;
	int		stepY;
	int		mapX;
	int		mapY;
	int		num_cols = 500; // for testing
	// int		num_rows = 500; // for testing

	//set initial player position
	playerY = 250;
	playerX = 200;

	//init var side to track which side of the wall has been hit (e.g. 0 --> N or S; 1 --> E or W ??)
	side = 0;
	
	// set viewing direction (--> west)
	viewX = -1;
	viewY = 0;
	
	// set camera plane position
	planeY = 0.66; // --> this determines how wide the FOV is (together with viewX or viewY respectively)
	planeX = 0; // because viewX != 0 and viewY == 0; otherwise would not be perpendicular
	
	// run the game loop
	x = 0;
	while (x < num_cols) // probably terminating condition to be redefined
	{
		// go through each column x
		while (x < num_cols)
		{
			// init hit flag
			hit = 0;

			// set the position within the array we are currently at; for every ray initialized with the starting position
			mapX = (int)playerX;
			mapY = (int)playerY;
			
			// calc ray position and direction
			cameraX = ((double)2 * (double)x / (double)num_cols) - (double)1; // for traversing the camera plane with increasing x / basically casting a new ray for every new x
			rayDirX = viewX + planeX * cameraX;
			rayDirY = viewY + planeY * cameraX;

			// size of increments from one x-side/y-side to the next x-side/y-side using pythagoras
			// deltaDistX = sqrt(1 + (rayDirY * rayDirY) / rayDirX * rayDirX);
			// deltaDistY = sqrt(1 + (rayDirX * rayDirX) / rayDirY * rayDirY);

			// size of increments from one x-side/y-side to the next x-side/y-side; simplified pythagoras and making the assumption that only the *ratio* between deltaDistX and deltaDistY matters for the DDA
			deltaDistX = 1 / rayDirX; // make sure to not divide by zero?
			if (deltaDistX < 0)
				deltaDistX *= -1;
			deltaDistY = 1 / rayDirY; // make sure to not divide by zero?
			if (deltaDistY < 0)
				deltaDistY *= -1;

			// calc matrix step (int) and length of ray from the initial position to the next side/line of the raster; required for DDA
			if (rayDirX < 0)
			{
				stepX = -1;
				sideDistX = (playerX - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - playerX) * deltaDistX;
			}
			if (rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (playerY - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - playerY) * deltaDistY;
			}
			
			// apply DDA
			// for "moving" along the ray and checking for intersections/hits
			while (hit == 0)
			{
				if (sideDistX < sideDistY)
				{
					sideDistX += deltaDistX;
					mapX += stepX;
					side = 0; // to check which side has been hit (NS or EW?)
				}
				else
				{
					sideDistY += deltaDistY;
					mapY += stepY;
					side = 1; // to check which side has been hit (NS or EW?)
				}
				mlx_pixel_put(vars->mlx, vars->win, mapX, mapY, 16777215);
				if (map[mapY][mapX] > 0)
					hit = 1;
			}
			x++;
		}
	}
	return (0);
}

int	ft_draw_map(t_vars *vars)
{
	int	map[500][500];
	int	y = 0;
	int	x = 0;
	
	while (y < 500)
	{
		x = 0;
		while (x < 500)
		{
			if (y == 0 || y == 499)
			{
				map[y][x] = 1;
				mlx_pixel_put(vars->mlx, vars->win, x, y, 65280);
			}
			else if (x == 0 || x == 499)
			{
				map[y][x] = 1;
				mlx_pixel_put(vars->mlx, vars->win, x, y, 65280);
			}
			else
				map[y][x] = 0;
			x++;
		}
		y++;
	}
	x = 50;
	y = 60;
	while (y < 300)
	{
		map[y][50] = 1;
		mlx_pixel_put(vars->mlx, vars->win, x, y, 65280);
		y++;
	}
	map[250][200] = 9; // position of the player
	cast_rays(map, vars);
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
	mlx_hook(vars.win, 12, 1L << 15, ft_draw_map, &vars);
	mlx_hook(vars.win, 17, 0L, ft_close, &vars);
	mlx_loop(vars.mlx);
	
	

	
}
