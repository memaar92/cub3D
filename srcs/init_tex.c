/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:15:35 by mamesser          #+#    #+#             */
/*   Updated: 2023/10/07 11:07:53 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

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
	v->tex_floor->img = mlx_xpm_file_to_image(v->mlx, "./textures/floor.xpm",
			&v->tex_floor->tex_w, &v->tex_floor->tex_h);
	if (!v->tex_floor->img)
		return (1);
	v->tex_floor->addr = (int *)mlx_get_data_addr(v->tex_floor->img,
			&v->tex_floor->bpp, &v->tex_floor->line_size,
			&v->tex_floor->endian);
	if (!v->tex_floor->addr)
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
	v->weapon->img = mlx_xpm_file_to_image(v->mlx, "./textures/gun.xpm",
			&v->weapon->tex_w, &v->weapon->tex_h);
	if (!v->weapon->img)
		return (1);
	v->weapon->addr = (int *)mlx_get_data_addr(v->weapon->img, &v->weapon->bpp,
			&v->weapon->line_size, &v->weapon->endian);
	if (!v->weapon->addr)
		return (1);
	v->cam_low->img = mlx_xpm_file_to_image(v->mlx,
			"./textures/cam.xpm", &v->cam_low->tex_w, &v->cam_low->tex_h);
	if (!v->cam_low->img)
		return (1);
	v->cam_low->addr = (int *)mlx_get_data_addr(v->cam_low->img,
			&v->cam_low->bpp, &v->cam_low->line_size, &v->cam_low->endian);
	if (!v->cam_low->addr)
		return (1);
	v->hand_tex_h = 512;
	v->hand_tex_w = 512;
	return (0);
}
