/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpanis@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:11:34 by valmpani          #+#    #+#             */
/*   Updated: 2023/09/25 17:00:44 by valmpani         ###   ########.fr       */
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

void	print_parser(t_vars *vars)
{
	printf(GREEN"\n----FL00R CEILING RGB-----\n");
	for (int i = 0; i < 2; i++)
	{

		for (int j = 0; j < 3; j++)
		{
			printf("%d ", vars->floor_ceiling[i][j]);
		}
		printf("\n");
	}
	printf("--------------------------\n"ESCAPE);
	printf(MAGENTA"\n----TEXTURES FILENAMES----\n");
	printf("SO %s\n", vars->textures[SO]);
	printf("NO %s\n", vars->textures[NO]);
	printf("WE %s\n", vars->textures[WE]);
	printf("EA %s\n", vars->textures[EA]);
	printf("--------------------------\n"ESCAPE);
	print_map(&vars, vars->map);
}

void	print_map(t_vars **vars, int **map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < (*vars)->array_rows + 2)
	{
		j = -1;
		while (++j < (*vars)->array_cols + 1)
		{
			if (map[i][j] == 9)
				printf(GREEN"•"ESCAPE);
			else if (map[i][j] == 0)
				printf(WHITE"■"ESCAPE);
			else if (map[i][j] == 1)
				printf(BLACK"%d"ESCAPE, map[i][j]);
			else if (map[i][j] == 7)
				printf(RED"%d"ESCAPE, map[i][j]);
			else if (map[i][j] == 2)
				printf(MAGENTA"%d"ESCAPE, map[i][j]);
		}
		printf("\n");
	}
}
