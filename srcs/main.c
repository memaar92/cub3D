/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpanis@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:09:45 by mamesser          #+#    #+#             */
/*   Updated: 2023/10/03 18:11:20 by valmpani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	ft_close(t_vars *vars)
{
	free_all_mem(vars);
	exit(0);
}

void	ft_usleep(long time)
{
	long	i;

	i = 0;
	while (i < time)
		i++;
}

int	handle_mouse(int x, int y, t_vars *vars)
{
	vars->counter++;
	if (vars->counter / 20 == 1)
	{
		if (vars->mouse_flag)
		{
			if (x < vars->screen_width / 2)
				player_rotate(65361, vars);
			else
				player_rotate(65363, vars);
			vars->turning_point = x;
		}
		vars->counter = 0;
	}
}

int	mouse_click(int button, int x, int y, t_vars *vars)
{
	if (button == 1)
		vars->mouse_flag = !vars->mouse_flag;
	ft_render(vars);
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
	vars->mouse_flag = 0;
	vars->turning_point = vars->screen_width / 2;
	vars->counter = 0;
	set_viewing_direction(vars);
	set_camera_plane(vars);
	mlx_mouse_hook(vars->win, &mouse_click, vars);
	mlx_hook(vars->win, 6, 1L << 6, handle_mouse, vars);
	mlx_hook(vars->win, 12, 1L << 15, ft_render, vars);
	mlx_hook(vars->win, 17, 0L, ft_close, vars);
	mlx_hook(vars->win, 02, 1L << 0, move_view, vars);
	mlx_loop(vars->mlx);
}
