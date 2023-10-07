/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:23:33 by mamesser          #+#    #+#             */
/*   Updated: 2023/10/07 10:38:30 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	init_screen_buffer(t_vars *vars)
{
	vars->scr_buf->img = mlx_new_image(vars->mlx, vars->screen_width,
			vars->screen_height);
	if (!vars->scr_buf->img)
		return (1);
	vars->scr_buf->addr = (int *)mlx_get_data_addr(vars->scr_buf->img,
			&vars->scr_buf->bpp, &vars->scr_buf->line_size,
			&vars->scr_buf->endian);
	if (!vars->scr_buf->addr)
		return (1);
	return (0);
}

int	set_color(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
