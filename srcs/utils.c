/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:23:33 by mamesser          #+#    #+#             */
/*   Updated: 2023/10/03 16:17:46 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	init_screen_buffer(t_vars *vars)
{
	vars->scr_buf = malloc(sizeof(t_img));
	if (!vars->scr_buf)
		return (1);
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

int	init_texture_dir(t_vars *vars, t_img *tex, int dir)
{
	tex->img = mlx_xpm_file_to_image(vars->mlx, vars->textures[dir],
			&tex->tex_w, &tex->tex_h);
	if (!tex->img)
		return (1);
	tex->addr = (int *)mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_size, &tex->endian);
	if (!tex->addr)
		return (1);
	return (0);
}

int	init_textures(t_vars *vars)
{
	vars->tex_no = malloc(sizeof(t_img));
	if (!vars->tex_no)
		return (1);
	vars->tex_so = malloc(sizeof(t_img));
	if (!vars->tex_so)
		return (1);
	vars->tex_we = malloc(sizeof(t_img));
	if (!vars->tex_we)
		return (1);
	vars->tex_ea = malloc(sizeof(t_img));
	if (!vars->tex_ea)
		return (1);
	vars->tex_h = 128;
	vars->tex_w = 128;
	if (init_texture_dir(vars, vars->tex_no, 0))
		return (1);
	if (init_texture_dir(vars, vars->tex_so, 1))
		return (1);
	if (init_texture_dir(vars, vars->tex_we, 2))
		return (1);
	if (init_texture_dir(vars, vars->tex_ea, 3))
		return (1);
	return (0);
}

int	set_color(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
