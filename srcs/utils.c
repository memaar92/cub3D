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

char	*set_char(char *buf, char c)
{
	int	i;

	i = 0;
	if (!buf)
		return (NULL);
	while (buf[i] != '\n' && buf[i] != '\0')
	{
		printf("%c", buf[i]);
		i++;
	}
	printf("\n");
	return (NULL);
}
