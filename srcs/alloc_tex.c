/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_tex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 11:07:44 by mamesser          #+#    #+#             */
/*   Updated: 2023/10/07 11:48:12 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	alloc_tex_walls(t_vars *vars)
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
	return (0);
}

void	set_to_zero(t_vars *vars)
{
	ft_bzero(vars->tex_no, sizeof(t_img));
	ft_bzero(vars->tex_so, sizeof(t_img));
	ft_bzero(vars->tex_we, sizeof(t_img));
	ft_bzero(vars->tex_ea, sizeof(t_img));
	ft_bzero(vars->scr_buf, sizeof(t_img));
	ft_bzero(vars->tex_floor, sizeof(t_img));
	ft_bzero(vars->tex_ceil, sizeof(t_img));
	ft_bzero(vars->weapon, sizeof(t_img));
	ft_bzero(vars->cam_low, sizeof(t_img));
}

int	alloc_tex_mem(t_vars *vars)
{
	if (alloc_tex_walls(vars))
		return (1);
	vars->scr_buf = malloc(sizeof(t_img));
	if (!vars->scr_buf)
		return (1);
	vars->tex_floor = malloc(sizeof(t_img));
	if (!vars->tex_floor)
		return (1);
	vars->tex_ceil = malloc(sizeof(t_img));
	if (!vars->tex_ceil)
		return (1);
	vars->weapon = malloc(sizeof(t_img));
	if (!vars->weapon)
		return (1);
	vars->cam_low = malloc(sizeof(t_img));
	if (!vars->cam_low)
		return (1);
	set_to_zero(vars);
	return (0);
}
