/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:51:19 by mamesser          #+#    #+#             */
/*   Updated: 2023/05/18 12:33:49 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	needle_len;

	i = 0;
	needle_len = ft_strlen(needle);
	if (!(*needle))
		return ((char *)haystack);
	else
	{
		while (haystack[i] && needle_len <= len - i)
		{
			if (haystack[i] == needle[0])
			{
				if (ft_strncmp(&haystack[i], needle, needle_len) == 0)
					return ((char *)&haystack[i]);
			}
			i++;
		}
		return (NULL);
	}
}
