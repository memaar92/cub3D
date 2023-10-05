/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:35:09 by valmpani          #+#    #+#             */
/*   Updated: 2023/10/04 14:36:50 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	is_valid_pos(t_vars *vars, int i, int j)
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

int	adjust_colors(int color, double factor)
{
	int	red;
	int	green;
	int	blue;

	red = (int)(((color >> 16) & 0xFF) * factor);
	green = (int)(((color >> 8) & 0xFF) * factor);
	blue = (int)((color & 0xFF) * factor);
	if (red > 255)
		red = 255;
	else if (blue > 255)
		blue = 255;
	else if (green > 255)
		green = 255;
	return (red << 16 | green << 8 | blue);
}

void	draw_circle(t_vars *vars, t_circle mp, int i, int j)
{
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
					vars->scr_buf->addr[j
						*(vars->scr_buf->line_size / 4) + i] = 0;
				else
					vars->scr_buf->addr[j
						*(vars->scr_buf->line_size / 4) + i] = 11382186;
			}
		}
	}
}

void	draw_half_circle(t_vars *vars, t_circle mp, int i, int j)
{
	int		color;

	mp.offset = vars->screen_height / 2.5;
	i = mp.center_x - mp.radius;
	while (i++ <= mp.center_x + mp.radius)
	{
		j = mp.center_y - mp.radius + mp.offset;
		while (j++ <= mp.center_y)
		{
			mp.distance = pow(i - mp.center_x, 2)
				+ pow(j - (mp.center_y + mp.offset), 2);
			if (mp.distance < mp.radius * mp.radius)
			{
				if (mp.distance <= (pow(mp.radius, 2) - mp.radius * 5))
				{
					color = vars->scr_buf->addr[j
						*(vars->scr_buf->line_size / 4) + i];
					vars->scr_buf->addr[j
						*(vars->scr_buf->line_size / 4) + i]
						= adjust_colors(color, 1.5);
				}
			}
		}
	}
}
