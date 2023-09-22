/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpanis@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:12:01 by valmpani          #+#    #+#             */
/*   Updated: 2023/09/22 09:38:36 by valmpani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	check_paths_ready(t_vars **vars, int *text_flag)
{
	int	i;

	i = -1;
	while ((*vars)->textures[++i])
	{
		if ((*vars)->textures[i][0] == '\0')
			return ;
	}
	*text_flag = 1;
}

int	find_paths(t_vars **vars, char **elements, int *text_flag)
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
	else if (ft_strncmp(elements[0], "EA", ft_strlen(elements[0])) == 0
		&& ft_strlen(elements[0]) == 2)
		texture = EA;
	if (access(elements[1], O_RDONLY) == -1)
		return (printf("Error: Please provide valid texture paths.\n"), 1);
	if ((*vars)->textures[texture][0])
		return (printf("Error: Please provide the correct texture info.\n"), 1);
	free((*vars)->textures[texture]);
	(*vars)->textures[texture] = ft_strdup(elements[1]);
	if (!(*vars)->textures[texture])
		return (printf("Error: Problem with malloc\n"), 1);
	check_paths_ready(vars, text_flag);
	return (0);
}

int	find_ceiling_floor(t_vars **vars, char **buf, int *ceil_floor_flag)
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
	*ceil_floor_flag = 1;
	return (0);
}

int	parse(t_vars **vars, char *filename, int text_flag, int ceil_floor_flag)
{
	int		fd;
	char	*buf;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (printf("error\n"), 1);
	buf = get_next_line(fd);
	while ((!ceil_floor_flag || !text_flag) && buf)
	{
		if (buf && buf[0] != '\n')
		{
			set_char(&buf, ',');
			if (find_textures(vars, &buf, &text_flag, &ceil_floor_flag))
				return (free(buf), close(fd), 1);
		}
		free(buf);
		buf = get_next_line(fd);
	}
	return (0);
}
