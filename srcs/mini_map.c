/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpanis@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:44:10 by valmpani          #+#    #+#             */
/*   Updated: 2023/10/01 17:36:29 by valmpani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void draw_square(t_vars *vars, int x, int y, int size, int fill_color, int border_color)
{
	int start_x = x;
	int start_y = y;
	int end_x = x + size;
	int end_y = y + size;

	while (start_x <= end_x)
	{
		int current_y = start_y;
		while (current_y <= end_y)
		{
			if (start_x == x || start_x == end_x || current_y == y || current_y == end_y)
			{
				vars->scr_buf->addr[current_y * (vars->scr_buf->line_size / 4) + start_x] = border_color;
			}
			else
			{
				vars->scr_buf->addr[current_y * (vars->scr_buf->line_size / 4) + start_x] = fill_color;
			}
			current_y++;
		}
		start_x++;
	}
}

void	draw_player(t_vars *vars, int center_x, int radius)
{
	int	i;
	int	j;
	int	distance;

	i = center_x - radius;
	while (i++ <= center_x + radius)
	{
		j = center_x - radius;
		while (j++ <= center_x + radius)
		{
			distance = (i - center_x) * (i - center_x) + (j - center_x) * (j - center_x);
			if (distance <= radius * radius)
				vars->scr_buf->addr[(j) * (vars->scr_buf->line_size / 4) + (i)] = 12312433;
		}
	}
}

void	draw_direction(t_vars *vars, t_circle mp, int sq)
{
	int	i;

	i = -1;
	while (++i < 15)
		vars->scr_buf->addr[(int)(vars->ray->viewY * i + mp.pl_pixel_y + sq/2) * (vars->scr_buf->line_size / 4) + (int)(vars->ray->viewX * i + mp.pl_pixel_x + sq/2)] = 12312433;
}

int is_valid_pos(t_vars *vars, int i, int j)
{
	int	newx;
	int	newy;

	newx = (int)vars->pl_pos_x + i;
	newy = (int)vars->pl_pos_y + j;
	if (newx < 0 || newx > vars->array_cols)
		return (0);
	else if (newy < 0 || newy > vars->array_rows + 1)
		return (0);
	else
		return (1);
}

void	draw_map(t_vars *vars, t_circle mp)
{
	int	i;
	int	j;
	int	posx;
	int	posy;
	int	square_size;

	mp.side = sqrt(pow(mp.radius, 2) * 2);
	square_size = ((mp.radius) * sqrt(2)) / 40;
	posx = mp.center_y - mp.side / 2 + 5;
	j = -20;
	while (++j < 20)
	{
		i = -20;
		posy = mp.center_x - mp.side / 2;
		while (++i < 20)
		{
			if (is_valid_pos(vars, i, j))
			{
				if (i == 0 && j == 0)
				{
					draw_square(vars, posy, posx, square_size, GR, GR);
					mp.pl_pixel_x = posy;
					mp.pl_pixel_y = posx;
				}
				else if (vars->map[(int)vars->pl_pos_x + i]
					[(int)vars->pl_pos_y + j] == 1)
					draw_square(vars, posy, posx, square_size, WHT, GR);
				else if (!vars->map[(int)vars->pl_pos_x + i]
					[(int)vars->pl_pos_y + j])
					draw_square(vars, posy, posx, square_size, 0, 0);
			}
			else
				draw_square(vars, posy, posx, square_size, 0, 0);
			posy += square_size;
		}
		posx += square_size;
	}
	draw_direction(vars, mp, square_size);
}

void	mini_map(t_vars *vars)
{
	t_circle	mp;
	int			i;
	int			j;

	mp.center_x = vars->screen_width - vars->screen_width / 6;
	mp.center_y = vars->screen_height - vars->screen_height / 6;
	if (vars->screen_width < vars->screen_height)
		mp.radius = vars->screen_width / 6 - 5;
	else
		mp.radius = vars->screen_height / 6 - 5;
	i = mp.center_x - mp.radius;
	while (i++ <= mp.center_x + mp.radius)
	{
		j = mp.center_y - mp.radius;
		while (j++ <= mp.center_y + mp.radius)
		{
			mp.distance = pow(i - mp.center_x, 2) + pow(j - mp.center_y, 2);
			if (mp.distance < mp.radius * mp.radius)
			{
				if (mp.distance <= (pow(mp.radius, 2) - mp.radius * 5))
				{
					vars->scr_buf->addr[j * (vars->scr_buf->line_size / 4) + i] = 0;
					mp.new_distance = (pow(mp.radius, 2) - mp.radius * 5);
				}
				else
					vars->scr_buf->addr[j * (vars->scr_buf->line_size / 4) + i] = 11382186;
			}
		}
	}
	draw_map(vars, mp);
	// draw_direction(vars, circle.center_x);
}