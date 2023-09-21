/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpanis@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:12:01 by valmpani          #+#    #+#             */
/*   Updated: 2023/09/21 16:07:10 by valmpani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	find_textures(t_vars **vars, char *buf, int *text_flag, int *c_f_flag)
{
	char	**elements;
	int		i;

	if ((buf[0] == 'F' || buf[0] == 'C') && ft_ispace(buf[1]))
		set_char(&buf, ' ');
	elements = ft_split(buf, ','); //modify split to not split in quotes
	if (!elements)
		return (1);
	i = -1;
	while (elements[++i])
	{
		if ((ft_strncmp(elements[i], "F", ft_strlen(elements[i])) == 0
				&& ft_strlen(elements[i]) == 1) || (ft_strncmp(elements[i], "C",
					ft_strlen(elements[i])) == 0
				&& ft_strlen(elements[i]) == 1))
		{
			if (find_ceiling_floor(vars, elements, c_f_flag))
				return (free(elements), 1); // add ft_free to this libft
		}
	}
	
}

int	find_ceiling_floor(t_vars **vars, char **buf, int *ceil_floor_flag)
{
	int	i;
	int	j;
	int	flag;

	if (buf[0] == 'F')
		flag = F;
	else
		flag = C;
	i = 0;
	while (buf[++i])
	{
		if (i < 4)
		{
			(*vars)->floor_ceiling[flag][i - 1] = ft_atoi(buf[i]);
			if ((*vars)->floor_ceiling[flag][i - 1] < 0 || (*vars)->floor_ceiling[flag][i - 1] > 255)
				return (printf("Please provide the correct RGB values"), 1);
		}
	}
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
		return (1);
	while (!ceil_floor_flag)
	{
		buf = get_next_line(fd);
		set_char(&buf, ' ');
		if (find_textures(vars, buf, &text_flag, &ceil_floor_flag))
			return (free(buf), close(fd), 1);
		free(buf);
	}
}
