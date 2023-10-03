/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:54:59 by mamesser          #+#    #+#             */
/*   Updated: 2023/10/03 17:16:57 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	put_text_on_buf_scr(t_vars *vars)
{
	int		color;
	int		tex_x_pos;
	double	tex_y_steps;
	int		tex_y_pos;
	double	temp;

	calc_vline_start_end(vars);
	tex_x_pos = calc_texture_pos_x(vars);
	tex_y_steps = 1.0 * vars->tex_h / vars->ray->line_height;
	temp = (vars->ray->draw_start - vars->screen_height / 2
			+ vars->ray->line_height / 2) * tex_y_steps;
	vars->screen_y = vars->ray->draw_start;
	while (vars->screen_y < vars->ray->draw_end)
	{
		tex_y_pos = (int)temp & (vars->tex_h - 1);
		temp += tex_y_steps;
		color = get_pixel_color(tex_x_pos, tex_y_pos, vars);
		if (vars->ray->side == 1)
			color = (color >> 1) & 8355711;
		vars->scr_buf->addr[vars->screen_y * (vars->scr_buf->line_size / 4)
			+ vars->screen_x] = color;
		vars->screen_y++;
	}
}

void	run_dda(t_vars *vars)
{
	while (vars->ray->hit == 0)
	{
		if (vars->ray->sidedist_x < vars->ray->sidedist_y
			|| (vars->ray->sidedist_x == vars->ray->sidedist_y
				&& vars->ray->deltadist_x < vars->ray->deltadist_y))
		{
			dda_calc_sidedist_x(vars);
		}
		else
			dda_calc_sidedist_y(vars);
		if (vars->map[vars->ray->map_x][vars->ray->map_y] == 1)
			vars->ray->hit = 1;
	}
}

int	cast_rays(t_vars *vars)
{
	while (vars->screen_x < vars->screen_width)
	{
		init_raycast(vars);
		run_dda(vars);
		calc_line_height(vars);
		put_text_on_buf_scr(vars);
		vars->screen_x++;
	}
	return (0);
}

void	draw_floor_ceiling(t_vars *vars)
{
	int	i;
	int	j;
	int	floor_color;
	int	ceiling_color;

	i = -1;
	floor_color = set_color(0, vars->floor_ceiling[0][0],
			vars->floor_ceiling[0][1], vars->floor_ceiling[0][2]);
	ceiling_color = set_color(0, vars->floor_ceiling[1][0],
			vars->floor_ceiling[1][1], vars->floor_ceiling[1][2]);
	while (++i < vars->screen_width)
	{
		j = -1;
		while (++j < vars->screen_height)
		{
			if (j <= vars->screen_height / 2)
				vars->scr_buf->addr[j * (vars->scr_buf->line_size / 4) + i]
					= ceiling_color;
			else
				vars->scr_buf->addr[j * (vars->scr_buf->line_size / 4) + i]
					= floor_color;
		}
	}
}

int	ft_render(t_vars *vars)
{
	draw_floor_ceiling(vars);
	vars->screen_x = 0;
	cast_rays(vars);
	mini_map(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->scr_buf->img, 0, 0);
	return (0);
}
