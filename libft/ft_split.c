/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:48:39 by mamesser          #+#    #+#             */
/*   Updated: 2023/06/06 16:29:52 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int		words;
	int		flag;
	size_t	i;

	words = 0;
	flag = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && flag == 0)
		{
			words++;
			flag = 1;
		}
		else if (s[i] == c)
			flag = 0;
		i++;
	}
	return (words);
}

void	*free_mem(char **ret)
{
	int	i;

	i = 0;
	while (ret[i])
		free(ret[i++]);
	free(ret);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	size_t	start;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	ret = malloc((count_words(s, c) + 1) * sizeof(*ret));
	if (!ret)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i + 1] && s[i + 1] != c)
				i++;
			ret[j] = ft_substr(s, start, i + 1 - start);
			if (!ret[j++])
				return (free_mem(ret));
		}
		i++;
	}
	ret[j] = NULL;
	return (ret);
}
