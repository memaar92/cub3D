/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpanis@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:11:34 by valmpani          #+#    #+#             */
/*   Updated: 2023/09/21 17:18:30 by valmpani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

char	*set_char(char *buf, char c)
{
	int		i;
	char	*final;

	i = -1;
	final = ft_calloc(sizeof(char), ft_strlen(buf));
	while (buf[++i])
	{
		if (ft_isspace(buf[i]) || buf[i] == c)
			final[i] = ' ';
		else
			final[i] = buf[i];
	}
	return (final);
}
