/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:44:10 by valmpani          #+#    #+#             */
/*   Updated: 2023/10/01 14:09:56 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	draw_square(t_vars *vars, t_circle mp, int color, int border)
{
	int	end_x;
	int	end_y;
	int	st;
	int	current_y;

	end_x = mp.posy + mp.square_size;
	end_y = mp.posx + mp.square_size;
	st = mp.posy;
	while (st <= end_x)
	{
		current_y = mp.posx;
		while (current_y <= end_y)
		{
			if (st == mp.posy || st == end_x || current_y == mp.posx
				|| current_y == end_y)
				vars->scr_buf->addr[current_y
					* (vars->scr_buf->line_size / 4) + st] = border;
			else
				vars->scr_buf->addr[current_y
					* (vars->scr_buf->line_size / 4) + st] = color;
			current_y++;
		}
		st++;
	}
}

void	draw_direction(t_vars *vars, t_circle mp)
{
	int	i;

	i = -1;
	while (++i < 10)
		vars->scr_buf->addr[(int)(vars->ray->viewY
				* i + mp.pl_pixel_y + mp.square_size / 2)
			* (vars->scr_buf->line_size / 4)
			+ (int)(vars->ray->viewX * i
				+ mp.pl_pixel_x + mp.square_size / 2)] = DR;
}

void	draw_block(t_vars *vars, t_circle *mp, int i, int j)
{
	if (is_valid_pos(vars, i, j))
	{
		if (i == 0 && j == 0)
		{
			draw_square(vars, *mp, GR, 0);
			mp->pl_pixel_x = mp->posy;
			mp->pl_pixel_y = mp->posx;
		}
		else if (vars->map[(int)vars->pl_pos_x + i]
			[(int)vars->pl_pos_y + j] == 1)
			draw_square(vars, *mp, WHT, GR);
		else if (!vars->map[(int)vars->pl_pos_x + i]
			[(int)vars->pl_pos_y + j])
			draw_square(vars, *mp, 0, 0);
	}
	else
		draw_square(vars, *mp, 0, 0);
}

void	draw_map(t_vars *vars, t_circle mp)
{
	int	i;
	int	j;
	int	square_size;

	mp.side = sqrt(pow(mp.radius, 2) * 2);
	mp.square_size = ((mp.radius) * sqrt(2)) / 40;
	square_size = ((mp.radius) * sqrt(2)) / 40;
	mp.posx = mp.center_y - mp.side / 2 + 5;
	j = -22;
	while (++j < 20)
	{
		i = -26;
		mp.posy = mp.center_x - mp.side / 2;
		while (++i < 20)
		{
			draw_block(vars, &mp, i, j);
			mp.posy += mp.square_size;
		}
		mp.posx += mp.square_size;
	}
	draw_direction(vars, mp);
}

void	mini_map(t_vars *vars)
{
	t_circle	mp;

	mp.center_x = vars->screen_width / 2;
	mp.center_y = vars->screen_height;
	mp.radius = vars->screen_width / 3;
	draw_half_circle(vars, mp, 0, 0);
	mp.center_x = vars->screen_width - vars->screen_width / 6;
	mp.center_y = vars->screen_height - vars->screen_height / 6;
	if (vars->screen_width < vars->screen_height)
		mp.radius = vars->screen_width / 6 - 5;
	else
		mp.radius = vars->screen_height / 6 - 5;
	draw_circle(vars, mp, 0, 0);
	draw_map(vars, mp);
}
