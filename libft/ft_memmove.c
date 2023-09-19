/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:48:00 by mamesser          #+#    #+#             */
/*   Updated: 2023/07/08 17:32:58 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (!dst && !src)
		return (NULL);
	if (src > dst)
	{
		while (i < len)
		{
			((char *)dst)[i] = ((const char *)src)[i];
			i++;
		}
	}
	else
	{
		while (len > 0)
		{
			((char *)dst)[len - 1] = ((const char *)src)[len - 1];
			len--;
		}
	}
	return ((void *)dst);
}
