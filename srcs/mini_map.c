/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpanis@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:44:10 by valmpani          #+#    #+#             */
/*   Updated: 2023/09/30 11:41:47 by valmpani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	draw_square(t_vars *vars, int x, int y, int size, int color)
{
	int	start_x = x;
	int	start_y = y;
	int	end_x = x + size;
	int	end_y = y + size;

	while (start_x < end_x)
	{
		int current_y = start_y;
		while (current_y < end_y)
		{
			vars->scr_buf->addr[y * (vars->scr_buf->line_size / 4) + x] = color;
			// mlx_pixel_put(vars->mlx, vars->win, start_x, current_y, color);
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

void	draw_direction(t_vars *vars, int center_x)
{
	int	i;

	i = -1;
	while (++i < 15)
		vars->scr_buf->addr[(int)(vars->ray->viewY * i + center_x) * (vars->scr_buf->line_size / 4) + (int)(vars->ray->viewX * i) + center_x] = 12312433;
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

void	draw_map(t_vars *vars, int center_x)
{
	int	i;
	int	j;
	int posx;
	int posy;
	int	square_size;
	
	posx = vars->screen_width - vars->screen_width / 2;
	square_size = 10;
	j = -4;
	while (++j < 8)
	{
		i = -4;
		posy = posx = vars->screen_width - vars->screen_width / 2;
		while (++i < 8)
		{
			if (is_valid_pos(vars, i, j))
			{
				if (i == 0 && j == 0)
				{
					draw_player(vars, posx, 4);
					draw_direction(vars, posx);
				}
				else if (vars->map[(int)vars->pl_pos_x + i][(int)vars->pl_pos_y + j])
				{
					printf("hello\n");
					draw_square(vars, posy, posx, square_size, 16777215);
				}
				else
					draw_square(vars, posy, posx, square_size, 0);
			}
			posy += square_size;
		}
		posx += square_size;
	}
}

void	mini_map(t_vars *vars)
{
	int	center_x;
	int	radius;
	int	i;
	int	j;
	int	distance;

	center_x = vars->screen_width - vars->screen_width / 6;
	radius = vars->screen_width / 6 - 5;
	i = center_x - radius;
	while (i++ <= center_x + radius)
	{
		j = center_x - radius;
		while (j++ <= center_x + radius)
		{
			distance = (i - center_x) * (i - center_x) + (j - center_x) * (j - center_x);
			if (distance < radius * radius)
			{
				// Check if the distance is less than 5 pixels from the center
				if (distance <= (radius * radius - radius * 10))
					vars->scr_buf->addr[(j) * (vars->scr_buf->line_size / 4) + (i)] = 0; // White
				else
					vars->scr_buf->addr[(j) * (vars->scr_buf->line_size / 4) + (i)] = 16777215; // Black
			}
		}
	}
	// draw_direction(vars, center_x);
	// draw_player(vars, center_x);
	draw_map(vars, center_x);
}
