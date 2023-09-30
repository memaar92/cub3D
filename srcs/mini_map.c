/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpanis@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:44:10 by valmpani          #+#    #+#             */
/*   Updated: 2023/09/29 19:29:04 by valmpani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	draw_player(t_vars *vars, int center_x)
{
	int	radius;
	int	i;
	int	j;
	int	distance;

	radius = 4;
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
	printf("view x: %f\n", vars->ray->viewX);
	printf("view x: %f\n", vars->ray->viewY);
	printf("\n");
}

void	mini_map(t_vars *vars)
{
	int	center_x;
	int	radius;
	int	i;
	int	j;
	int	distance;

//	i = -1;
//	while (++i <= 150)
//	{
//		j = -1;
//		while (++j <= 150)
//		{
//			if (i == 0 || i == 150) {
//				for (int k = 0; k < 5; ++k) {
//					vars->scr_buf->addr[(vars->screen_height - j - k) * (vars->scr_buf->line_size / 4) +
//										(vars->screen_width - i - k)] = 16777215;
//				}
//			}
//			else if (j == 0 || j == 150)
//			{
//				for (int k = 0; k < 5; ++k)
//				{
//					vars->scr_buf->addr[(vars->screen_height - j - k) * (vars->scr_buf->line_size / 4) + (vars->screen_width - i - k)] = 16777215;
//				}
//			}
//			else
//				vars->scr_buf->addr[(vars->screen_height - j) * (vars->scr_buf->line_size / 4) + (vars->screen_width - i)] = 0;
//		}
//	}
	center_x = vars->screen_width - 80;
	radius = 75;
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
	draw_direction(vars, center_x);
	draw_player(vars, center_x);
}
