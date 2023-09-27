/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpanis@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:23:03 by valmpani          #+#    #+#             */
/*   Updated: 2023/09/27 13:31:08 by valmpani         ###   ########.fr       */
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

void	set_map(t_vars **vars, int **map, int i, char *line)
{
	int	j;

	j = -1;
	while (line && line[++j] != '\n' && line[j])
	{
		if (line[j] == '0' || line[j] == '1')
			map[j + 1][i] = '2' - line[j];
		else if (ft_isspace(line[j]))
			map[j + 1][i] = 2;
		else
		{
			map[j + 1][i] = 7;
			(*vars)->pl_pos_x = (double)j + 1;
			(*vars)->pl_pos_y = (double)i;
		}
	}
}

char	*reach_map(t_vars **vars, int fd, int *i)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (close(fd), NULL);
	while (++(*i) <= (*vars)->map_pos)
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

int	get_map_size(t_vars **vars, char *filename, int i)
{
	int		fd;
	char	*line;

	i = -1;
	fd = open(filename, O_RDONLY);
	line = reach_map(vars, fd, &i);
	if (!line)
		return (close(fd), 1);
	while (line)
	{
		if (!is_not_empty_line(line))
		{
			free(line);
			break ;
		}
		i++;
		if ((int)ft_strlen(line) > (*vars)->array_cols)
		{
			(*vars)->array_cols = (int)ft_strlen(line);
			if (!ft_strchr(line, '\n'))
				(*vars)->array_cols += 1;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	(*vars)->array_rows = i - (*vars)->map_pos;
	return (0);
}
