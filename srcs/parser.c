/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:12:01 by valmpani          #+#    #+#             */
/*   Updated: 2023/09/26 14:31:39 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

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

char	*parse_textures(t_vars **vars, char *filename)
{
	int		fd;
	char	*buf;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (printf("error\n"), NULL);
	i = 0;
	buf = get_next_line(fd);
	while (buf && (!is_first_line(buf) || !is_not_empty_line(buf)))
	{
		(*vars)->map_pos++;
		if (buf[0] != '\n')
		{
			set_char(&buf, ' ');
			if (find_textures(vars, &buf))
				return (free(buf), close(fd), NULL);
		}
		free(buf);
		buf = get_next_line(fd);
	}
	return (buf);
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

int get_map_size(t_vars **vars, char *filename)
{
	int		i;
	int		fd;
	char	*line;

	i = -1;
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), 1);
	while (++i <= (*vars)->map_pos)
	{
		free(line);
		line = get_next_line(fd);
	}
	while (line)
	{
		if (!is_not_empty_line(line))
			break ;
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

int	floodfill(t_vars **vars, int **map, double x, double y)
{
	int	result;

	if ((int)x < 0 || (int)x >= (*vars)->array_rows + 2
		|| (int)y < 0 || (int)y >= (*vars)->array_cols
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

int	**test_map(t_vars **vars)
{
	int		**map;
	int		i;
	int		j;

	map = ft_calloc(sizeof(int *), (*vars)->array_rows + 2);
	if (!map)
		return (NULL);
	i = -1;
	while (++i < (*vars)->array_rows + 2)
	{
		j = -1;
		map[i] = ft_calloc(sizeof(int), (*vars)->array_cols + 1);
		if (!map[i])
			return (NULL);
		while (++j < (*vars)->array_cols + 1)
		{
			map[i][j] = 9;
		}
	}
	return (map);
}

int flood_the_map(t_vars **vars, int fd)
{
	int		**map;
	char	*line;
	int		i;
	int		j;

	map = test_map(vars);
	i = 0;
	line = get_next_line(fd);
	while (++i < (*vars)->array_rows + 1)
	{
		j = -1;
		while (line[++j] != '\n' && line[j])
		{
			if (line[j] == '0' || line[j] == '1')
				map[i][j + 1] = '2' - line[j];
			else if (ft_isspace(line[j]))
				map[i][j + 1] = 2;
			else
			{
				map[i][j + 1] = 7;
				(*vars)->pl_pos_x = (double)i;
				(*vars)->pl_pos_y = (double)j;
			}
		}
		free(line);
		line = get_next_line(fd);
	}
	// print_map(vars, map);
	if (floodfill(vars, map, (*vars)->pl_pos_x, (*vars)->pl_pos_y))
		return (free(map), 1); // free it correctly
	else
		(*vars)->map = map;
	return (0);
}

int create_map(t_vars **vars, char *filename)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), 1);
	while (++i < (*vars)->map_pos)
	{
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	if (flood_the_map(vars, fd))
		return (0);
	return (1);
}


int	parse_map(t_vars **vars, int fd, char *filename)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (not_valid_character(vars, line))
			return (free(line), 1);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	if (get_map_size(vars, filename))
		return (1);
	if (!create_map(vars, filename))
		return (1);
	return (0);
}


int	parse(t_vars **vars, char *filename)
{
	int		i;
	int		fd;
	char	*first_line;

	first_line = parse_textures(vars, filename);
	if (!first_line)
		return (printf(MAP_ERR"\n"), 1);
	if (textures_not_filled(vars))
		return (printf(MAP_ERR"\n"), free(first_line), 1);
	i = -1;
	fd = open(filename, O_RDONLY);
	free(first_line);
	while (++i < (*vars)->map_pos)
	{
		first_line = get_next_line(fd);
		free(first_line);
	}
	if (parse_map(vars, fd, filename))
		return (printf(MAP_ERR"\n"), 1);
	return (0);
}
