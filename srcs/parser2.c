/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:43:08 by valmpani          #+#    #+#             */
/*   Updated: 2023/09/22 13:43:11 by valmpani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	find_textures(t_vars **vars, char **buf, int *text_flag, int *c_f_flag)
{
	char	**elements;

	if (!(*buf))
		return (1);
	if (((*buf)[0] == 'F' || (*buf)[0] == 'C') && ft_isspace((*buf)[1]))
		set_char(buf, ',');
	elements = ft_split(*buf, ' ');
	if (!elements)
		return (printf("split\n"), 1);
	if (check_floor_ceil(vars, elements, c_f_flag))
		return (free_mem(elements), 1);
	else if (check_textures(vars, elements, text_flag))
		return (free_mem(elements), 1);
	return (free_mem(elements), 0);
}

int	check_floor_ceil(t_vars **vars, char **elements, int *c_f_flag)
{
	if ((ft_strncmp(elements[0], "F", ft_strlen(elements[0])) == 0
			&& ft_strlen(elements[0]) == 1) || (ft_strncmp(elements[0], "C",
				ft_strlen(elements[0])) == 0 && ft_strlen(elements[0]) == 1))
	{
		if (find_ceiling_floor(vars, elements, c_f_flag))
			return (1);
	}
	return (0);
}

int	check_textures(t_vars **vars, char **elements, int *text_flag)
{
	if ((ft_strncmp(elements[0], "SO", ft_strlen(elements[0])) == 0
			&& ft_strlen(elements[0]) == 2) || (ft_strncmp(elements[0],
				"NO", ft_strlen(elements[0])) == 0
			&& ft_strlen(elements[0]) == 2) || (ft_strncmp(elements[0],
				"WE", ft_strlen(elements[0])) == 0
			&& ft_strlen(elements[0]) == 2) || (ft_strncmp(elements[0],
				"EA", ft_strlen(elements[0])) == 0
			&& ft_strlen(elements[0]) == 2))
		if (find_paths(vars, elements, text_flag))
			return (1);
	return (0);
}
