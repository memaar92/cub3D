/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:11:34 by valmpani          #+#    #+#             */
/*   Updated: 2023/10/07 10:07:47 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	set_char(char **buf, char c)
{
	int		i;
	char	quote;

	i = -1;
	quote = '\0';
	if (!(*buf))
		return ;
	while ((*buf)[++i])
	{
		if (((*buf)[i] == '\'' || (*buf)[i] == '\"') && !quote)
			quote = (*buf)[i];
		else if (((*buf)[i] == '\'' || (*buf)[i] == '\"') && quote)
			quote = '\0';
		if ((*buf)[i] == c || ft_isspace((*buf)[i]))
			(*buf)[i] = ' ';
	}
}

int	is_not_empty_line(char *buf)
{
	int	i;

	i = -1;
	while (buf[++i])
	{
		if (!ft_isspace(buf[i]))
			return (1);
	}
	return (0);
}

int	is_first_line(char *buf)
{
	int	i;

	i = -1;
	if (buf[0])
	{
		while (buf[++i])
			if (buf[i] != '1' && !ft_isspace(buf[i]) && buf[i] != '0'
				&& buf[i] != 'N' && buf[i] != 'S'
				&& buf[i] != 'W' && buf[i] != 'E')
				return (0);
	}
	return (1);
}

int	check_rgb_values(t_vars **vars, char **buf)
{
	int	i;
	int	flag;

	if ((*buf)[0] == 'F')
		flag = F;
	else
		flag = C;
	i = 0;
	while (buf[++i])
	{
		if (i < 4)
		{
			if ((*vars)->floor_ceiling[flag][i - 1] != -1)
				return (printf("Please provide the correct parameters.\n"), 1);
			(*vars)->floor_ceiling[flag][i - 1] = ft_atoi(buf[i]);
			if ((*vars)->floor_ceiling[flag][i - 1] < 0
				|| (*vars)->floor_ceiling[flag][i - 1] > 255)
				return (printf("Please provide the correct RGB values\n"), 1);
		}
	}
	if (i != 4)
		return (printf("Please provide the correct RGB values\n"), 1);
	return (0);
}

int	right_file_extension(char *name)
{
	char	**split;
	int		i;

	split = ft_split(name, '.');
	i = 0;
	while (split[i])
		i++;
	if (i != 2)
		return (free_mem(split), 1);
	if (ft_strncmp(split[1], "cub", ft_strlen(split[1])) != 0
		|| ft_strlen(split[1]) != 3)
		return (free_mem(split), 1);
	return (free_mem(split), 0);
}
