/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpanis@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:12:01 by valmpani          #+#    #+#             */
/*   Updated: 2023/09/23 09:15:05 by valmpani         ###   ########.fr       */
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
		if (!ft_isspace(line[i]) && line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W' && line[i] != '0' && line[i] != '1')
			return (1);
		if ((line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W') && (*vars)->pov_dir != -1)
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
		if (ft_strlen(line) > (*vars)->array_cols)
			(*vars)->array_cols = ft_strlen(line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	(*vars)->array_rows = i - (*vars)->map_pos;
//	printf("----------MAP----------\n");
//	printf("HEIGHT: %zu\n", (*vars)->array_rows);
//	printf("WIDTH:  %zu\n", (*vars)->array_cols);
//	printf("-----------------------\n");
	return (0);
}

int	**test_map(t_vars **vars)
{
	int		**map;
	size_t	i;
	size_t	j;

	map = ft_calloc(sizeof(int *), (*vars)->array_rows + 2);
	if (!map)
		return (NULL);
	i = -1;
	while (++i < (*vars)->array_rows + 2)
	{
		j = -1;
		map[i] = ft_calloc(sizeof(int), (*vars)->array_cols + 2);
		if (!map[i])
			return (NULL);
		while (++j < (*vars)->array_cols + 2)
		{
			map[i][j] = 9;
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
	return (map);
}

int flood_the_map(t_vars **vars, int fd)
{
	int		**map;
	char	*line;
	size_t	i;
	size_t	j;

	map = test_map(vars);
	i = 0;
	line = get_next_line(fd);
	while (++i < (*vars)->array_rows)
	{
		j = 0;
		map[i] = ft_calloc(sizeof(int), (*vars)->array_cols);
		if (!map[i])
			return (1);
		while (line[++j] != '\n' && line[j])
		{
			if (i == 0 || i == (*vars)->array_rows + 1)
				map[i][j] = 9;
			if (line[j] == '0' || line[j] == '1')
				map[i][j] = line[j] - '0';
			else
				map[i][j] = 7;
			printf("%d ", map[i][j]);
		}
		printf("\n");
		free(line);
		line = get_next_line(fd);
	}
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
		return (1);
	return (0);
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
		return (printf("Error: Please provide a valid map.\n"), 1);
	if (textures_not_filled(vars))
		return (printf("Error: Please provide a valid map.\n"), free(first_line), 1);
	i = -1;
	fd = open(filename, O_RDONLY);
	free(first_line);
	while (++i < (*vars)->map_pos)
	{
		first_line = get_next_line(fd);
//		if (i != pos -1)
		free(first_line);
	}
	if (parse_map(vars, fd, filename))
		return (printf("Error: Please provide a valid map.\n"), 1);
	return (0);
}
