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

int	zoom_pos(t_vars *vars, double x, double y)
{
	int	next_x;
	int	next_y;

	next_x = vars->pl_pos_x + x * 1.05;
	next_y = vars->pl_pos_y + y * 1.05;
	if (!vars->map[(int)(vars->pl_pos_x + x)][(int)(vars->pl_pos_y + y)] &&
		!vars->map[next_x][next_y])
	{
		vars->pl_pos_x += x / 4;
		vars->pl_pos_y += y / 4;
		return (0);
	}
	else
		return (1);
}

void	find_zoom_pos(t_vars *vars)
{
	int	i;

	i = -1;
	while (++i < ZOOM_FACTOR)
	{
		if (vars->zoom)
		{
			if (zoom_pos(vars, vars->ray->view_x, vars->ray->view_y))
				break ;
			else
				vars->zoom_reps++;
		}
		else if (i < vars->zoom_reps)
		{
			if (zoom_pos(vars, -vars->ray->view_x, -vars->ray->view_y))
				break ;
			if (i == vars->zoom_reps - 1)
				vars->zoom_reps = 0;
		}
	}
	ft_render(vars);
}

int	mouse_click(int button, int x, int y, t_vars *vars)
{
	(void)x;
	(void)y;
	if (button == 3 && !vars->zoom)
	{
		vars->zoom = 1;
		find_zoom_pos(vars);
	}
	else if (button == 3 && vars->zoom)
	{
		vars->zoom = 0;
		find_zoom_pos(vars);
	}
	if (button == 1)
		vars->mouse_flag = !vars->mouse_flag;
	return (0);
}
