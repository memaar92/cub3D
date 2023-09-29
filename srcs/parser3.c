/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpanis@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:23:03 by valmpani          #+#    #+#             */
/*   Updated: 2023/09/27 13:48:14 by valmpani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

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

void	set_map_cols(t_vars **vars, char *line, int *i)
{
	(*i)++;
	if ((int)ft_strlen(line) > (*vars)->array_cols)
	{
		(*vars)->array_cols = (int)ft_strlen(line);
		if (!ft_strchr(line, '\n'))
			(*vars)->array_cols += 1;
	}
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
			break ;
		set_map_cols(vars, line, &i);
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	(*vars)->array_rows = i - (*vars)->map_pos;
	return (close(fd), 0);
}
