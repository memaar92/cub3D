/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:09:45 by mamesser          #+#    #+#             */
/*   Updated: 2023/10/03 14:37:53 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	ft_close(t_vars *vars)
{
	free_all_mem(vars);
	exit(0);
}

int	right_file_extension(char *name)
{
	char	**split;
	int		i;

	split = ft_split(name, '.');
	i = 0;
	while (split[i])
		i++;
	if (i != 2)
		return (free_mem(split), 1);
	if (ft_strncmp(split[1], "cub", ft_strlen(split[1])) != 0
		|| ft_strlen(split[1]) != 3)
		return (free_mem(split), 1);
	return (free_mem(split), 0);
}

int	main(int argc, char **argv)
{
	t_vars	*vars;
	
	if (argc != 2)
		return(printf("ERROR: Please provide a map.\n"), 1);
	if (right_file_extension(argv[1]))
		return(printf("ERROR: Please provide map with .cub extension.\n"), 1);
	vars = init_vars();
	if (!vars)
		return (printf("ERROR\n"), 1);
	if (parse(&vars, argv[1]))
		return(free_all_mem(vars), 1);
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (free_all_mem(vars), 1);
	vars->win = mlx_new_window(vars->mlx, vars->screen_width, vars->screen_height, "Title");
	if (!vars->win)
		return (free_all_mem(vars), 1);
	if (init_screen_buffer(vars))
		return (free_all_mem(vars), 1);
	if (init_textures(vars))
		return (free_all_mem(vars), 1);
	mlx_hook(vars->win, 12, 1L << 15, ft_render, vars);
	mlx_hook(vars->win, 17, 0L, ft_close, vars);
	mlx_hook(vars->win, 02, 1L<<0, move_view, vars);
	mlx_loop(vars->mlx);
}
