/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_item.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:22:31 by mamesser          #+#    #+#             */
/*   Updated: 2023/10/05 17:52:29 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	get_hand_item_color(int tex_x_pos, int tex_y_pos, t_vars *vars)
{
	int	color;
	int	pos;
	double x;
	double y;

	x = (double)tex_x_pos;
	y = ((double)tex_y_pos);
	pos = y * (vars->cam_low->line_size / 4) + x;
	color = (int)(vars->cam_low->addr[pos]);
	// else
	// {
	// 	pos = y * (vars->cam_low->line_size / 4) + x;
	// 	color = (int)(vars->cam_low->addr[pos]);
	// 	vars->frame = 0;
	// }
	return (color);
}


void	add_hand_item(t_vars *vars) // still need to remove hard-coded texture values
{
	int	color;
	int	i = -1;
	int	j = 0;
	// double	scale = (((double)vars->screen_width / (double)512) + ((double)vars->screen_height / (double)512)) / 1.95; // scale used for gun
	double	scale = (((double)vars->screen_width / (double)512) + ((double)vars->screen_height / (double)512)) / 4; // scale used for camera
	int	tex_x = 0;
	int	tex_y = 512 - 1;
	double	steps = 1 / (double)scale;
	double	temp_y = (double)tex_y;
	double	temp_x = 0.0;
	
	while (++i < (int)(512 * scale))
	{
		tex_x = (int)(temp_x);
		temp_x += steps;
		j = (int)(512 * scale);
		tex_y = 512 - 1;
		temp_y = (double)tex_y;
		while (--j >= 0)
		{
			tex_y = (int)(temp_y);
			temp_y -= steps;
			color = get_hand_item_color(tex_x, tex_y, vars);
			if (color != 0)
				vars->scr_buf->addr[(vars->screen_height - (int)(512 * scale) + j) *(vars->scr_buf->line_size / 4) + (vars->screen_width / 2 - ((int)(512 * scale / 1.8)) + i)] = color;	
		}
	}
}
