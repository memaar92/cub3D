/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:49:34 by mamesser          #+#    #+#             */
/*   Updated: 2023/05/15 11:49:38 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	else
	{
		while (i < n - 1 && s1[i]
			&& (unsigned char)s1[i] == (unsigned char)s2[i])
			i++;
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
}
