/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:09:45 by mamesser          #+#    #+#             */
/*   Updated: 2023/09/28 19:14:38 by mamesser         ###   ########.fr       */
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

int	ft_pl_move(int keycode, t_vars *vars)
{
	if (keycode == KEY_W)
	{
		vars->pl_pos_x += vars->ray->viewX;
		vars->pl_pos_y += vars->ray->viewY;
	}
	else if (keycode == KEY_S)
	{
		vars->pl_pos_x -= vars->ray->viewX;
		vars->pl_pos_y -= vars->ray->viewY;
	}
	if (keycode == KEY_A)
	{
		vars->pl_pos_x += vars->ray->viewY;
		vars->pl_pos_y -= vars->ray->viewX;
	}
	else if (keycode == KEY_D)
	{
		vars->pl_pos_x -= vars->ray->viewY;
		vars->pl_pos_y += vars->ray->viewX;
	}
	mlx_clear_window(vars->mlx, vars->win);
	draw_floor_ceiling(vars);
	vars->screen_x = 0;
	cast_rays(vars);
	return (0);
}

void	player_rotate(int keycode, t_vars *vars)
{
	double	temp;

	if (keycode == 65361)
	{
		temp = vars->ray->viewX;
		vars->ray->viewX = cos(-ROT) * temp + (-sin(-ROT)) * vars->ray->viewY;
		vars->ray->viewY = sin(-ROT) * temp + cos(-ROT) * vars->ray->viewY;
		temp = vars->ray->planeX;
		vars->ray->planeX = cos(-ROT) * temp + (-sin(-ROT)) * vars->ray->planeY;
		vars->ray->planeY = sin(-ROT) * temp + cos(-ROT) * vars->ray->planeY;
	}
	if (keycode == 65363)
	{
		printf("%f\n", ROT);
		temp = vars->ray->viewX;
		vars->ray->viewX = cos(ROT) * temp + (-sin(ROT)) * vars->ray->viewY;
		vars->ray->viewY = sin(ROT) * temp + cos(ROT) * vars->ray->viewY;
		temp = vars->ray->planeX;
		vars->ray->planeX = cos(ROT) * temp + (-sin(ROT)) * vars->ray->planeY;
		vars->ray->planeY = sin(ROT) * temp + cos(ROT) * vars->ray->planeY;
	}
	mlx_clear_window(vars->mlx, vars->win);
	draw_floor_ceiling(vars);
	vars->screen_x = 0;
	cast_rays(vars);
}


int	move_view(int keycode, t_vars *vars)
{
	printf("%d\n", keycode);
	if (keycode == KEY_W || keycode == KEY_S
		|| keycode == KEY_A || keycode == KEY_D)
		ft_pl_move(keycode, vars);
	if (keycode == 65361 || keycode == 65363)
	{
		player_rotate(keycode, vars);
	}
}

int	main(int argc, char **argv)
{
	t_vars	*vars;
	// create a 2D int array (this will later be created from the parsed .cub map)
	
	if (argc != 2)
		return(printf("ERROR\n"), 1);
	// init mlx and creating the display/window
	vars = init_vars();
	vars->ray = malloc(sizeof(t_ray));
	vars->screen_width = 500;
	vars->screen_height = 500;
	if (parse(&vars, argv[1]))
		return(printf("ERROR\n"), 1);
	// print_parser(vars);
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (1);
	vars->win = mlx_new_window(vars->mlx, vars->screen_width, vars->screen_height, "Title");
	if (!vars->win)
		return (free(vars->mlx), 1);
	if (init_screen_buffer(vars))
		return (1);
	if (init_textures(vars))
		return (1);
	mlx_hook(vars->win, 12, 1L << 15, ft_render, vars);
	mlx_hook(vars->win, 17, 0L, ft_close, vars);
	mlx_key_hook(vars->win, &move_view, vars);
	mlx_loop(vars->mlx);

}

// int main(int argc, char **argv)

// {
// 	t_vars *vars;

// 	if (argc != 2)
// 		return(printf("ERROR\n"), 1);
// 	vars = init_vars();
// 	if (parse(&vars, argv[1]))
// 		return(printf("ERROR\n"), 1);
// 	print_parser(vars);
// 	return (0);
// }
