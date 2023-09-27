/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpanis@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 10:01:04 by valmpani          #+#    #+#             */
/*   Updated: 2023/09/27 13:48:22 by valmpani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	floodfill(t_vars **vars, int **map, double x, double y)
{
	int	result;

	if ((int)x < 0 || (int)x >= (*vars)->array_cols + 1
		|| (int)y < 0 || (int)y >= (*vars)->array_rows + 2
		|| map[(int)x][(int)y] == 1 || map[(int)x][(int)y] == 0)
		return (0);
	else if (map[(int)x][(int)y] == 9)
		return (1);
	map[(int)x][(int)y] = 0;
	result = floodfill(vars, map, x + 1, y);
	if (!result)
		result = floodfill(vars, map, x -1, y);
	if (!result)
		result = floodfill(vars, map, x, y + 1);
	if (!result)
		result = floodfill(vars, map, x, y - 1);
	return (result);
}

int	flood_the_map(t_vars **vars, int fd)
{
	int		**map;
	char	*line;
	int		i;

	map = test_map(vars);
	i = 0;
	line = get_next_line(fd);
	while (++i < (*vars)->array_cols + 1)
	{
		set_map(vars, map, i, line);
		free(line);
		line = get_next_line(fd);
	}
	if (floodfill(vars, map, (*vars)->pl_pos_x, (*vars)->pl_pos_y))
		return (free_map(*vars, map), 1);
	else
		(*vars)->map = map;
	return (0);
}

int	textures_not_filled(t_vars **vars)
{
	int	i;
	int	j;

	i = 0;
	while ((*vars)->textures[i])
		i++;
	if (i != 4)
		return (1);
	i = -1;
	while (++i < 2)
	{
		j = -1;
		while (++j < 3)
		{
			if ((*vars)->floor_ceiling[i][j] == -1)
				return (1);
		}
	}
	return (0);
}

int	find_paths(t_vars **vars, char **elements)
{
	int	texture;

	if (ft_strncmp(elements[0], "NO", ft_strlen(elements[0])) == 0
		&& ft_strlen(elements[0]) == 2)
		texture = NO;
	else if (ft_strncmp(elements[0], "SO", ft_strlen(elements[0])) == 0
		&& ft_strlen(elements[0]) == 2)
		texture = SO;
	else if (ft_strncmp(elements[0], "WE", ft_strlen(elements[0])) == 0
		&& ft_strlen(elements[0]) == 2)
		texture = WE;
	else
		texture = EA;
	if (access(elements[1], F_OK) == -1)
		return (printf("Error: Please provide valid texture paths.\n"), 1);
	if ((*vars)->textures[texture])
		return (printf("Error: Please provide the correct texture info.\n"), 1);
	(*vars)->textures[texture] = ft_strdup(elements[1]);
	if (!(*vars)->textures[texture])
		return (printf("Error: Problem with malloc\n"), 1);
	return (0);
}

int	find_ceiling_floor(t_vars **vars, char **buf)
{
	int	i;
	int	j;

	if (check_rgb_values(vars, buf))
		return (1);
	i = -1;
	while (++i < 2)
	{
		j = -1;
		while (++j < 3)
			if ((*vars)->floor_ceiling[i][j] == -1)
				return (0);
	}
	return (0);
}
