/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:09:45 by mamesser          #+#    #+#             */
/*   Updated: 2023/10/07 11:05:47 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	ft_close(t_vars *vars)
{
	free_all_mem(vars);
	exit(0);
}

void	run_hooks(t_vars *vars)
{
	mlx_mouse_hook(vars->win, &mouse_click, vars);
	mlx_hook(vars->win, 6, 1L << 6, mouse_move, vars);
	mlx_hook(vars->win, 12, 1L << 15, ft_render, vars);
	mlx_hook(vars->win, 17, 0L, ft_close, vars);
	mlx_hook(vars->win, 02, 1L << 0, move_view, vars);
	mlx_loop(vars->mlx);
}

int	main(int argc, char **argv)
{
	t_vars	*vars;

	if (argc < 2)
		return (printf("Error: Please provide a map.\n"), 1);
	if (argc > 3)
		return (printf(ARG_ERR"Specify third arg for bonus.\n"), 1);
	if (right_file_extension(argv[1]))
		return (printf("Error: Please provide map with .cub extension.\n"), 1);
	vars = init_vars(argc);
	if (!vars)
		return (printf("Error\n"), 1);
	if (parse(&vars, argv[1]))
		return (free_all_mem(vars), 1);
	if (init_mlx(vars))
		return (free_all_mem(vars), 1);
	if (init_tex_and_scr_buf(vars))
		return (printf("Error\n"), free_all_mem(vars), 1);
	set_viewing_direction(vars);
	set_camera_plane(vars);
	run_hooks(vars);
}
