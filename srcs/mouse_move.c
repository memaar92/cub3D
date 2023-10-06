/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:28:49 by mamesser          #+#    #+#             */
/*   Updated: 2023/10/06 18:29:05 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	mouse_move(int x, int y, t_vars *vars)
{
	(void)y;
	vars->rot_flag = 1;
	vars->counter++;
	if (vars->counter / 7 == 1)
	{
		if (vars->mouse_flag)
		{
			if (x < vars->screen_width / 2)
				player_rotate(65361, vars);
			else
				player_rotate(65363, vars);
		}
		vars->counter = 0;
	}
	return (0);
}

void	find_zoom_pos(t_vars *vars)
{
	int	i;

	i = -1;
	while (++i < ZOOM_FACTOR)
	{
		if (vars->zoom)
		{
			if (new_pos(vars, vars->ray->view_x, vars->ray->view_y))
				break ;
		}
		else
		{
			if (new_pos(vars, -vars->ray->view_x, -vars->ray->view_y))
				break ;
		}
	}
	ft_render(vars);
}

void	zoom(t_vars *vars) // while not calling find_zoom directly?
{
	find_zoom_pos(vars);
}

int	mouse_click(int button, int x, int y, t_vars *vars)
{
	(void)x;
	(void)y;
	if (button == 3 && !vars->zoom)
	{
		vars->zoom = 1;
		zoom(vars);
	}
	else if (button == 3 && vars->zoom)
	{
		vars->zoom = 0;
		zoom(vars);
	}
	if (button == 1)
		vars->mouse_flag = !vars->mouse_flag;
	return (0);
}
