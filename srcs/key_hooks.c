/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpanis@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:10:41 by valmpani          #+#    #+#             */
/*   Updated: 2023/10/01 13:20:41 by valmpani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	new_pos(t_vars *vars, double x, double y)
{
	int	next_x;
	int	next_y;

	// next_x = (int)(vars->pl_pos_x + 1.05 * x);
	// next_y = (int)(vars->pl_pos_y + 1.05 * y);
	if (!vars->map[(int)(vars->pl_pos_x + x)][(int)(vars->pl_pos_y + y)])
	{
		// && !vars->map[next_x][next_y]
		vars->pl_pos_x += x;
		vars->pl_pos_y += y;
	}
}

int	ft_pl_move(int keycode, t_vars *vars)
{
	if (keycode == KEY_W)
		new_pos(vars, vars->ray->viewX, vars->ray->viewY);
	else if (keycode == KEY_S)
		new_pos(vars, -vars->ray->viewX, -vars->ray->viewY);
	if (keycode == KEY_A)
		new_pos(vars, -vars->ray->planeX, -vars->ray->planeY);
	else if (keycode == KEY_D)
		new_pos(vars, vars->ray->planeX, vars->ray->planeY);
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
	if (keycode == KEY_W || keycode == KEY_S
		|| keycode == KEY_A || keycode == KEY_D)
		ft_pl_move(keycode, vars);
	if (keycode == 65361 || keycode == 65363)
	{
		player_rotate(keycode, vars);
	}
	return (0);
}
