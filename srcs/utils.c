/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpanis@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:11:34 by valmpani          #+#    #+#             */
/*   Updated: 2023/09/22 09:45:49 by valmpani         ###   ########.fr       */
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

void	print_parser(t_vars *vars)
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			printf("%d\n", vars->floor_ceiling[i][j]);
		}
	}
	printf("SO %s\n", vars->textures[SO]);
	printf("NO %s\n", vars->textures[NO]);
	printf("WE %s\n", vars->textures[WE]);
	printf("EA %s\n", vars->textures[EA]);
}
