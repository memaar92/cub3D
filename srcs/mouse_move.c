/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:28:49 by mamesser          #+#    #+#             */
/*   Updated: 2023/10/03 18:32:40 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	mouse_move(int x, int y, t_vars *vars)
{
	(void)y;
	vars->counter++;
	if (vars->counter / 10 == 1)
	{
		if (vars->mouse_flag)
		{
			if (x < vars->screen_width / 2)
				player_rotate(65361, vars);
			else
				player_rotate(65363, vars);
		}
		vars->counter = 0;
	}
	return (0);
}

int	mouse_click(int button, int x, int y, t_vars *vars)
{
	(void)x;
	(void)y;
	if (button == 1)
		vars->mouse_flag = !vars->mouse_flag;
	return (0);
}
