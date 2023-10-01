/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpanis@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:44:10 by valmpani          #+#    #+#             */
/*   Updated: 2023/10/01 13:38:13 by valmpani         ###   ########.fr       */
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
			vars->scr_buf->addr[current_y * (vars->scr_buf->line_size / 4) + start_x] = color;
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
		vars->scr_buf->addr[(int)(vars->ray->viewY * i + 828) * (vars->scr_buf->line_size / 4) + (int)(vars->ray->viewX * i + 828)] = 12312433;
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
	
	posx = center_x;
	square_size = vars->screen_width / 210;
	j = -20;
	while (++j < 20)
	{
		i = -20;
		posy = center_x;
		while (++i < 20)
		{
			if (is_valid_pos(vars, i, j))
			{
				if (i == 0 && j == 0)
				{
					// draw_player(vars, posx, 4);
					// draw_direction(vars, posx);
					draw_square(vars, posy, posx, square_size, 11382186);
					printf("x %d y %d\n", posx, posy);					
				
				}
				else if (vars->map[(int)vars->pl_pos_x + i][(int)vars->pl_pos_y + j] == 1)
				{
					draw_square(vars, posy, posx, square_size, 16777215);
				}
				else if (!vars->map[(int)vars->pl_pos_x + i][(int)vars->pl_pos_y + j])
				{
					draw_square(vars, posy, posx, square_size, 0);
				}
				// printf("x:%f y:%f\n", vars->pl_pos_x + i, vars->pl_pos_y + j);
			}
			posy += square_size;
		}
		posx += square_size;
		printf("\n");
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
				if (distance <= (radius * radius - radius * 5))
					vars->scr_buf->addr[(j) * (vars->scr_buf->line_size / 4) + (i)] = 0;
				else
					vars->scr_buf->addr[(j) * (vars->scr_buf->line_size / 4) + (i)] = 11382186;
			}
		}
	}
	draw_map(vars, vars->screen_width - vars->screen_width / 4);
	// draw_player(vars, center_x, 4);
	draw_direction(vars, center_x);
	// draw_square(vars, 300, 300, 10, 16777215);
}
