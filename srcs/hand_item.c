/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_item.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:22:31 by mamesser          #+#    #+#             */
/*   Updated: 2023/10/07 11:40:52 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	get_hand_item_color(int x, int y, t_vars *vars)
{
	int		color;
	int		pos;

	color = 0;
	if (vars->hand_item == 0)
	{
		pos = y * (vars->weapon->line_size / 4) + x;
		color = (int)(vars->weapon->addr[pos]);
	}
	else
	{
		pos = y * (vars->cam_low->line_size / 4) + x;
		color = (int)(vars->cam_low->addr[pos]);
	}
	return (color);
}

void	init_hand_item_vars(t_vars *vars)
{
	vars->item->x = -1;
	vars->item->y = 0;
	if (vars->frame % 3 == 0 && vars->rot_flag == 0)
		vars->item->scale = ((vars->screen_width / (double)vars->hand_tex_w)
				+ (vars->screen_height / (double)vars->hand_tex_h)) / 1.955;
	else if (vars->frame % 2 == 0 && vars->rot_flag == 0)
		vars->item->scale = ((vars->screen_width / (double)vars->hand_tex_w)
				+ (vars->screen_height / (double)vars->hand_tex_h)) / 1.95;
	else
		vars->item->scale = ((vars->screen_width / (double)vars->hand_tex_w)
				+ (vars->screen_height / (double)vars->hand_tex_h)) / 1.945;
	vars->item->tex_x = 0;
	vars->item->tex_y = vars->hand_tex_h - 1;
	vars->item->steps = 1 / (double)vars->item->scale;
	vars->item->temp_y = (double)vars->item->tex_y;
	vars->item->temp_x = 0.0;
}

void	put_item_to_screen(t_vars *vars)
{
	int	y;
	int	x_scaling;

	y = vars->screen_height - (int)(vars->hand_tex_h
			* vars->item->scale) + vars->item->y;
	x_scaling = ((int)(vars->hand_tex_w * vars->item->scale / 1.8));
	vars->scr_buf->addr[y * (vars->scr_buf->line_size / 4)
		+ (vars->screen_width / 2 - x_scaling + vars->item->x)]
		= vars->item->color;
}

void	add_hand_item(t_vars *vars)
{
	init_hand_item_vars(vars);
	while (++vars->item->x < (int)(vars->hand_tex_w * vars->item->scale))
	{
		vars->item->tex_x = (int)(vars->item->temp_x);
		vars->item->temp_x += vars->item->steps;
		vars->item->y = (int)(vars->hand_tex_h * vars->item->scale);
		vars->item->tex_y = vars->hand_tex_h - 1;
		vars->item->temp_y = (double)vars->item->tex_y;
		while (--vars->item->y >= 0)
		{
			vars->item->tex_y = (int)(vars->item->temp_y);
			vars->item->temp_y -= vars->item->steps;
			vars->item->color = get_hand_item_color(vars->item->tex_x,
					vars->item->tex_y, vars);
			if (vars->item->color != 0)
				put_item_to_screen(vars);
		}
	}
}
