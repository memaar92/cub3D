/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:12:01 by valmpani          #+#    #+#             */
/*   Updated: 2023/10/09 14:10:50 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

char	*parse_textures(t_vars **vars, char *filename)
{
	int		fd;
	char	*buf;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (printf("error\n"), NULL);
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
	if (!buf)
		printf("Error: Please provide a map.\n");
	return (buf);
}

int	**test_map(t_vars **vars)
{
	int		**map;
	int		i;
	int		j;

	map = ft_calloc(sizeof(int *), (*vars)->array_cols + 1);
	if (!map)
		return (NULL);
	i = -1;
	while (++i < (*vars)->array_cols + 1)
	{
		j = -1;
		map[i] = ft_calloc(sizeof(int), (*vars)->array_rows + 2);
		if (!map[i])
			return (NULL);
		while (++j < (*vars)->array_rows + 2)
		{
			map[i][j] = 9;
		}
	}
	return (map);
}

int	create_map(t_vars **vars, char *filename)
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
	if (get_map_size(vars, filename, 0))
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
		return (1);
	if (textures_not_filled(vars))
		return (free(first_line), 1);
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
