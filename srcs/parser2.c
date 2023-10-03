/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:43:08 by valmpani          #+#    #+#             */
/*   Updated: 2023/10/03 14:48:13 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	find_textures(t_vars **vars, char **buf)
{
	char	**elements;

	if (!(*buf))
		return (1);
	if (((*buf)[0] == 'F' || (*buf)[0] == 'C') && ft_isspace((*buf)[1]))
		set_char(buf, ',');
	elements = ft_split(*buf, ' ');
	if (!elements)
		return (1);
	if (check_floor_ceil(vars, elements))
		return (free_mem(elements), 1);
	else if (check_textures(vars, elements))
		return (free_mem(elements), 1);
	return (free_mem(elements), 0);
}

int	check_floor_ceil(t_vars **vars, char **elements)
{
	if ((ft_strncmp(elements[0], "F", ft_strlen(elements[0])) == 0
			&& ft_strlen(elements[0]) == 1) || (ft_strncmp(elements[0], "C",
				ft_strlen(elements[0])) == 0 && ft_strlen(elements[0]) == 1))
	{
		if (find_ceiling_floor(vars, elements))
			return (1);
	}
	return (0);
}

int	check_textures(t_vars **vars, char **elements)
{
	if ((ft_strncmp(elements[0], "SO", ft_strlen(elements[0])) == 0
			&& ft_strlen(elements[0]) == 2) || (ft_strncmp(elements[0],
				"NO", ft_strlen(elements[0])) == 0
			&& ft_strlen(elements[0]) == 2) || (ft_strncmp(elements[0],
				"WE", ft_strlen(elements[0])) == 0
			&& ft_strlen(elements[0]) == 2) || (ft_strncmp(elements[0],
				"EA", ft_strlen(elements[0])) == 0
			&& ft_strlen(elements[0]) == 2))
		if (find_paths(vars, elements))
			return (printf("Please provide valid texture path\n"), 1);
	return (0);
}

int	not_valid_character(t_vars **vars, char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (!ft_isspace(line[i]) && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
			&& line[i] != '0' && line[i] != '1')
			return (1);
		if ((line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
				|| line[i] == 'W') && (*vars)->pov_dir != -1)
			return (1);
		if (line[i] == 'N')
			(*vars)->pov_dir = NO;
		else if (line[i] == 'S')
			(*vars)->pov_dir = SO;
		else if (line[i] == 'W')
			(*vars)->pov_dir = WE;
		else if (line[i] == 'E')
			(*vars)->pov_dir = EA;
	}
	return (0);
}
