/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:23:33 by mamesser          #+#    #+#             */
/*   Updated: 2023/10/05 17:30:40 by mamesser         ###   ########.fr       */
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

int	init_wall_textures(t_vars *vars)
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
	vars->tex_h = 256;
	vars->tex_w = 256;
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

int	init_floor_ceil_textures(t_vars *v)
{
	v->tex_floor = malloc(sizeof(t_img));
	if (!v->tex_floor)
		return (1);
	v->tex_floor->img = mlx_xpm_file_to_image(v->mlx, "./textures/floor.xpm",
			&v->tex_floor->tex_w, &v->tex_floor->tex_h);
	if (!v->tex_floor->img)
		return (1);
	v->tex_floor->addr = (int *)mlx_get_data_addr(v->tex_floor->img, 
		&v->tex_floor->bpp, &v->tex_floor->line_size, &v->tex_floor->endian);
	if (!v->tex_floor->addr)
		return (1);
	v->tex_ceil = malloc(sizeof(t_img));
	if (!v->tex_ceil)
		return (1);
	v->tex_ceil->img = mlx_xpm_file_to_image(v->mlx, "./textures/tex_ceil.xpm",
			&v->tex_ceil->tex_w, &v->tex_ceil->tex_h);
	if (!v->tex_ceil->img)
		return (1);
	v->tex_ceil->addr = (int *)mlx_get_data_addr(v->tex_ceil->img,
		&v->tex_ceil->bpp, &v->tex_ceil->line_size, &v->tex_ceil->endian);
	if (!v->tex_ceil->addr)
		return (1);
	return (0);
}

int	init_hand_item_textures(t_vars *v)
{
	v->torch = malloc(sizeof(t_img));
	if (!v->torch)
		return (1);
	v->torch->img = mlx_xpm_file_to_image(v->mlx, "./textures/torch.xpm",
			&v->torch->tex_w, &v->torch->tex_h);
	if (!v->torch->img)
		return (1);
	v->torch->addr = (int *)mlx_get_data_addr(v->torch->img, &v->torch->bpp,
			&v->torch->line_size, &v->torch->endian);
	if (!v->torch->addr)
		return (1);
	v->cam_low = malloc(sizeof(t_img));
	if (!v->cam_low)
		return (1);
	v->cam_low->img = mlx_xpm_file_to_image(v->mlx,
		"./textures/camera_low2.xpm", &v->cam_low->tex_w, &v->cam_low->tex_h);
	if (!v->cam_low->img)
		return (1);
	v->cam_low->addr = (int *)mlx_get_data_addr(v->cam_low->img,
		&v->cam_low->bpp, &v->cam_low->line_size, &v->cam_low->endian);
	if (!v->cam_low->addr)
		return (1);
	return (0);
}

int	set_color(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
