/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:45:18 by mamesser          #+#    #+#             */
/*   Updated: 2023/05/15 11:45:19 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_abs(int n)
{
	if (n < 0)
		n = -n;
	return (n);
}

static int	ft_len_num(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*ret;
	int		len;

	len = ft_len_num(n);
	ret = malloc((len + 1) * sizeof(*ret));
	if (!ret)
		return (NULL);
	ret[len] = '\0';
	if (n == 0)
		ret[0] = '0';
	else if (n < 0)
		ret[0] = '-';
	while (n != 0)
	{
		ret[--len] = ft_abs(n % 10) + '0';
		n /= 10;
	}
	return (ret);
}
