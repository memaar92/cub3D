/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:35:09 by valmpani          #+#    #+#             */
/*   Updated: 2023/10/06 19:44:14 by mamesser         ###   ########.fr       */
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

void	draw_zoom_circle(t_vars *vars, t_circle mp, int i, int j)
{
	i = 0;
	mp.center_x = vars->screen_width / 2;
	mp.center_y = vars->screen_height / 2;
	mp.radius = vars->screen_height / 2.3;
	while (i++ <= vars->screen_width)
	{
		j = 0;
		while (j++ <= vars->screen_height)
		{
			mp.distance = pow(i - mp.center_x, 2) + pow(j - mp.center_y, 2);
			if (mp.distance > mp.radius * mp.radius
				|| i == vars->screen_width / 2 || j == vars->screen_height / 2)
			{
				vars->scr_buf->addr[j
					*(vars->scr_buf->line_size / 4) + i] = 0;
			}
		}
	}
}
