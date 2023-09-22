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

int	find_textures(t_vars **vars, char **buf, int *text_flag, int *c_f_flag)
{
	char	**elements;
	int		i;

	if (!(*buf))
		return (1);
	if (((*buf)[0] == 'F' || (*buf)[0] == 'C') && ft_isspace((*buf)[1]))
		set_char(buf, ',');
	elements = ft_split(*buf, ' '); //modify split to not split in quotes
	if (!elements)
		return (printf("split\n"), 1);
	if ((ft_strncmp(elements[0], "F", ft_strlen(elements[0])) == 0
			&& ft_strlen(elements[0]) == 1) || (ft_strncmp(elements[0], "C",
				ft_strlen(elements[0])) == 0
			&& ft_strlen(elements[0]) == 1))
	{
		if (find_ceiling_floor(vars, elements, c_f_flag))
			return (free(elements), 1); // add ft_free to this libft
	}
	return (0);
}

int	find_ceiling_floor(t_vars **vars, char **buf, int *ceil_floor_flag)
{
	int	i;
	int	j;
	int	flag;

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

int	parse(t_vars **vars, char *filename)
{
	int		fd;
	char	*buf;
	int		text_flag;
	int		ceil_floor_flag;

	text_flag = 0;
	ceil_floor_flag = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (printf("error\n"), 1);
	buf = get_next_line(fd);
	while (!ceil_floor_flag && buf)
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
