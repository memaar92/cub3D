/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:10:41 by valmpani          #+#    #+#             */
/*   Updated: 2023/10/03 17:18:19 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	new_pos(t_vars *vars, double x, double y)
{
	if (!vars->map[(int)(vars->pl_pos_x + x)][(int)(vars->pl_pos_y + y)])
	{
		vars->pl_pos_x += x;
		vars->pl_pos_y += y;
	}
}

int	ft_pl_move(int keycode, t_vars *vars)
{
	if (keycode == KEY_W)
		new_pos(vars, vars->ray->view_x, vars->ray->view_y);
	else if (keycode == KEY_S)
		new_pos(vars, -vars->ray->view_x, -vars->ray->view_y);
	if (keycode == KEY_A)
		new_pos(vars, -vars->ray->plane_x, -vars->ray->plane_y);
	else if (keycode == KEY_D)
		new_pos(vars, vars->ray->plane_x, vars->ray->plane_y);
	mlx_clear_window(vars->mlx, vars->win);
	ft_render(vars);
	return (0);
}

void	player_rotate(int keycode, t_vars *vars)
{
	double	temp;

	if (keycode == 65361)
	{
		temp = vars->ray->view_x;
		vars->ray->view_x = cos(-ROT) * temp + (-sin(-ROT)) * vars->ray->view_y;
		vars->ray->view_y = sin(-ROT) * temp + cos(-ROT) * vars->ray->view_y;
		temp = vars->ray->plane_x;
		vars->ray->plane_x = cos(-ROT) * temp + (-sin(-ROT))
			* vars->ray->plane_y;
		vars->ray->plane_y = sin(-ROT) * temp + cos(-ROT) * vars->ray->plane_y;
	}
	if (keycode == 65363)
	{
		temp = vars->ray->view_x;
		vars->ray->view_x = cos(ROT) * temp + (-sin(ROT)) * vars->ray->view_y;
		vars->ray->view_y = sin(ROT) * temp + cos(ROT) * vars->ray->view_y;
		temp = vars->ray->plane_x;
		vars->ray->plane_x = cos(ROT) * temp + (-sin(ROT)) * vars->ray->plane_y;
		vars->ray->plane_y = sin(ROT) * temp + cos(ROT) * vars->ray->plane_y;
	}
	mlx_clear_window(vars->mlx, vars->win);
	ft_render(vars);
}

int	move_view(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESCAPE)
		ft_close(vars);
	if (keycode == KEY_W || keycode == KEY_S
		|| keycode == KEY_A || keycode == KEY_D)
		ft_pl_move(keycode, vars);
	if (keycode == 65361 || keycode == 65363)
	{
		player_rotate(keycode, vars);
	}
	return (0);
}
