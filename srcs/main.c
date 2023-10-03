/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpanis@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:09:45 by mamesser          #+#    #+#             */
/*   Updated: 2023/10/03 17:37:28 by valmpani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	ft_close(t_vars *vars)
{
	free_all_mem(vars);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_vars	*vars;

	if (argc != 2)
		return (printf("ERROR: Please provide a map.\n"), 1);
	if (right_file_extension(argv[1]))
		return (printf("ERROR: Please provide map with .cub extension.\n"), 1);
	vars = init_vars();
	if (!vars)
		return (printf("ERROR\n"), 1);
	if (parse(&vars, argv[1]))
		return (free_all_mem(vars), 1);
	if (init_mlx(vars))
		return (free_all_mem(vars), 1);
	if (init_tex_and_scr_buf(vars))
		return (free_all_mem(vars), 1);
	set_viewing_direction(vars);
	set_camera_plane(vars);
	mlx_hook(vars->win, 12, 1L << 15, ft_render, vars);
	mlx_hook(vars->win, 17, 0L, ft_close, vars);
	mlx_hook(vars->win, 02, 1L << 0, move_view, vars);
	mlx_loop(vars->mlx);
}
