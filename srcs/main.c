/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:09:45 by mamesser          #+#    #+#             */
/*   Updated: 2023/09/27 13:44:44 by mamesser         ###   ########.fr       */
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
	mlx_hook(vars->win, 12, 1L << 15, ft_render, vars);
	mlx_hook(vars->win, 17, 0L, ft_close, vars);
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
