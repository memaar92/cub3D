/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:51:36 by mamesser          #+#    #+#             */
/*   Updated: 2023/07/12 13:01:25 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen2(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strchr_mod(const char *s, int c, size_t *line_len)
{
	while (s[*line_len])
	{
		if (s[*line_len] == (char)c)
		{
			(*line_len)++;
			return ((char *)s);
		}
		(*line_len)++;
	}
	if (s[*line_len] == (char)c)
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoin_mod(char *s1, char *s2)
{
	char	*ret;
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = ft_strlen2(s1) + ft_strlen2(s2);
	ret = malloc((len + 1) * sizeof(*ret));
	if (!ret)
		return (ft_free(s1, s2, 1));
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	while (s2[j])
		ret[i++] = s2[j++];
	ret[i] = '\0';
	free(s1);
	return (ret);
}
