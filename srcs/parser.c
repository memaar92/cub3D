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

char	*parse_textures(t_vars **vars, char *filename, int *pos)
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
		(*pos)++;
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

int	parse(t_vars **vars, char *filename)
{
	int		i;
	int		fd;
	int		pos;
	char	*first_line;

	pos = 0;
	first_line = parse_textures(vars, filename, &pos);
	if (!first_line)
		return (printf("Error: Please provide a valid map. 1\n"), 1);
	if (textures_not_filled(vars))
		return (printf("Error: Please provide a valid map. 2\n"), 1);
	i = -1;
	fd = open(filename, O_RDONLY);
	while (++i <= pos)
		first_line = get_next_line(fd);
	return (0);
}
