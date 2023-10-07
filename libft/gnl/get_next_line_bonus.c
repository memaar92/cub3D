/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:50:40 by mamesser          #+#    #+#             */
/*   Updated: 2023/07/12 13:01:44 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_free(char *collector, char *buf, int flag_both)
{
	if (flag_both == 0)
	{
		free(collector);
		collector = NULL;
	}
	else if (flag_both == 1)
	{
		free(buf);
		free(collector);
		collector = NULL;
	}
	return (NULL);
}

char	*ft_fill_coll(int fd, char *collector, int *end_flag, size_t *line_len)
{
	char	*buf;

	if (!collector)
	{
		collector = malloc(1);
		if (!collector)
			return (NULL);
		collector[0] = '\0';
	}
	buf = malloc((BUFFER_SIZE + 1) * sizeof(*buf));
	if (!buf)
		return (ft_free(collector, NULL, 0));
	while (*end_flag > 0 && !(ft_strchr_mod(collector, '\n', line_len)))
	{
		*end_flag = read(fd, buf, BUFFER_SIZE);
		if (*end_flag < 0)
			return (ft_free(collector, buf, 1));
		buf[*end_flag] = '\0';
		collector = ft_strjoin_mod(collector, buf);
		if (!collector)
			return (NULL);
	}
	free(buf);
	return (collector);
}

char	*ft_adj_collector(char *collector, size_t line_len, int end_flag)
{
	int		i;
	char	*ret;

	if (end_flag == 0)
		return (ft_free(collector, NULL, 0));
	ret = malloc((ft_strlen2(collector) - line_len + 1) * sizeof(*ret));
	if (!ret)
		return (ft_free(collector, NULL, 0));
	i = 0;
	while (collector[line_len])
		ret[i++] = collector[line_len++];
	ret[i] = '\0';
	free(collector);
	return (ret);
}

char	*ft_output(char *collector, size_t line_len, int end_flag)
{
	char	*ret;
	int		i;

	i = 0;
	if (end_flag == 0 && !collector[0])
		return (NULL);
	ret = malloc((line_len + 1) * sizeof(*ret));
	if (!ret)
		return (NULL);
	while (collector[i] && collector[i] != '\n')
	{
		ret[i] = collector[i];
		i++;
	}
	if (collector[i] == '\n')
		ret[i++] = '\n';
	ret[i] = '\0';
	return (ret);
}

char	*get_next_line(int fd)
{
	char	*collector[10240];
	char	*output;
	int		end_flag;
	size_t	line_len;

	line_len = 0;
	end_flag = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	collector[fd] = NULL;
	collector[fd] = ft_fill_coll(fd, collector[fd], &end_flag, &line_len);
	if (!collector[fd])
		return (NULL);
	output = ft_output(collector[fd], line_len, end_flag);
	if (!output)
	{
		free(collector[fd]);
		collector[fd] = NULL;
		return (NULL);
	}
	free(collector[fd]);
	return (output);
}

