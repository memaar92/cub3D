/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpanis@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:54:59 by mamesser          #+#    #+#             */
/*   Updated: 2023/09/23 09:14:52 by valmpani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

// int	ft_close(t_vars *vars)
// {
// 	if (vars->win)
// 		mlx_destroy_window(vars->mlx, vars->win);
// 	if (vars->mlx)
// 	{
// 		mlx_destroy_display(vars->mlx);
// 		free(vars->mlx);
// 	}
// 	exit(0);
// }
//
// int	ft_draw_map(t_vars *vars)
// {
// 	(void)vars;
// 	int side = 0;
// 	int	map[24][24];
// 	int	y = 0;
// 	int	x = 0;
//
// 	while (y < 24)
// 	{
// 		x = 0;
// 		while (x < 24)
// 		{
// 			if (y == 0 || y == 23)
// 				map[y][x] = 1;
// 			else if (x == 0 || x == 23)
// 				map[y][x] = 1;
// 			else
// 				map[y][x] = 0;
// 			x++;
// 		}
// 		y++;
// 	}
// 	x = 5;
// 	while (y < 12)
// 		map[y][5] = 1;
// 	map[10][10] = 9; // position of the player
// 	// viewing direction (--> west)
// 	double playerY = 10;
// 	double playerX = 10;
// 	double viewY = 0;
// 	double	viewX = -1;
//
// 	(void)viewX;
// 	(void)viewY;
//
// 	// camera plane position
// 	double	planeY = 0.66; // --> this determines how wide the FOV is (together with viewX or viewY respectively)
// 	double planeX = 0; // b/c viewX != 0 and viewY == 0; otherwise would not be perpendicular
//
// 	// game loop
// 	while (1)
// 	{
// 		// go through each column x
// 		while (x < 24)
// 		{
// 			// calc ray position and direction
// 			double cameraX = 2 * x / 24 - 1; // for traversing the camera plane with increasing x / basically casting a new ray for every new x
// 			double rayX = viewX + planeX * cameraX;
// 			double rayY = viewY + planeY * cameraX;
//
// 			// the position within the array we are currently at; initally at the starting position
// 			int mapX = (int)playerX;
// 			int mapY = (int)playerY;
//
// 			// length of ray from the initial position to the next side/line of the raster; required for DDA
// 			double sideDistX;
// 			double sideDistY;
//
// 			// size of increments from one x-side/y-side to the next x-side/y-side; simplified pythagoras and making the assumption that only the *ratio* between deltaDistX and deltaDistY matters for the DDA
// 			double lenRayX = 1 / rayX; // make sure to not divide by zero?
// 			if (lenRayX < 0)
// 				lenRayX *= -1;
// 			double lenRayY = 1 / rayY; // make sure to not divide by zero?
// 			if (lenRayY < 0)
// 				lenRayY *= -1;
//
// 			// what is this var exactly for? calc len of ray?
// 			double perpWallDist;
//
// 			// for "moving" along the ray and checking for intersections
// 			int stepX;
// 			int stepY;
// 			int hit = 0;
//
// 			// calc next step
// 			if (rayX < 0)
// 			{
// 				stepX = -1;
// 				sideDistX = (playerX - mapX) * lenRayX;
// 			}
// 			else
// 			{
// 				stepX = 1;
// 				sideDistX = (mapX + 1.0 - playerX) * lenRayX;
// 			}
// 			if (rayY < 0)
// 			{
// 				stepY = -1;
// 				lenRayY = (playerY - mapY) * lenRayY;
// 			}
// 			else
// 			{
// 				stepY = 1;
// 				lenRayY = (mapY + 1.0 - playerY) * lenRayY;
// 			}
//
// 			// apply DDA
// 			while (hit == 0)
// 			{
// 				if (sideDistX < sideDistY)
// 				{
// 					sideDistX += lenRayX;
// 					mapX += stepX;
// 					side = 0; // to check which side has been hit (NS or EW?)
// 				}
// 				else
// 				{
// 					sideDistY += lenRayY;
// 					mapY += stepY;
// 					side = 1; // to check which side has been hit (NS or EW?)
// 				}
// 				if (map[mapY][mapX] > 0) // check for hit
// 					hit = 1;
// 			}
// 			x++;
// 		}
// 	}
// 	return (0);
// }

int	main(int argc, char **argv)
{
	t_vars	*vars;

	if (argc > 2)
		return (printf("Incorrect number of arguments\n"), 1);
	vars = init_vars();
	if (!vars)
		return (1);
	// create a 2D int array (this will later be created from the parsed .cub map)
	// init mlx and creating the display/window
	if (parse(&vars, argv[1]))
		return (free(vars), 1);
	print_parser(vars);
//	vars->mlx = mlx_init();
//	if (!vars->mlx)
//		return (1);
//	vars->win = mlx_new_window(vars->mlx, 640, 480, "Title");
//	if (!vars->win)
//		return (free(vars->mlx), 1);
//	mlx_hook(vars->win, 12, 1L << 15, ft_draw_map, &vars);
//	mlx_hook(vars->win, 17, 0L, ft_close, &vars);
//	mlx_loop(vars->mlx);

//	free vars //
	return (0);
}
