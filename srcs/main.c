/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:09:45 by mamesser          #+#    #+#             */
/*   Updated: 2023/10/01 14:18:59 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	ft_close(t_vars *vars)
{
	free_map(vars, vars->map);
	free(vars->ray);
	free_mem(vars->textures);
	free_images(vars);
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
	free(vars);
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
		return (free_mem(split), 0);
	if (ft_strncmp(split[1], "cub", ft_strlen(split[1])) != 0
		|| ft_strlen(split[1]) != 3)
		return (free_mem(split), 0);
	return (free_mem(split), 1);
}

int	main(int argc, char **argv)
{
	t_vars	*vars;
	
	if (argc != 2)
		return(printf("ERROR\n"), 1);
	vars = init_vars();
	vars->ray = malloc(sizeof(t_ray));
	vars->screen_width = 1280;
	vars->screen_height = 720;
	if (parse(&vars, argv[1]))
		return(printf("ERROR\n"), 1);
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
	mlx_hook(vars->win, 02, 1L<<0, move_view, vars);
	mlx_loop(vars->mlx);
}
