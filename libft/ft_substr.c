/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:51:39 by mamesser          #+#    #+#             */
/*   Updated: 2023/05/18 10:45:41 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	len_s;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	len_s = ft_strlen(s);
	if (len_s - start < len)
		len = len_s - start;
	if (!len_s || start >= len_s)
		len = 0;
	ret = malloc((len + 1) * sizeof(*ret));
	if (!ret)
		return (NULL);
	while (s[i] && i < start)
		i++;
	while (s[i] && j < len)
		ret[j++] = s[i++];
	ret[j] = '\0';
	return (ret);
}
