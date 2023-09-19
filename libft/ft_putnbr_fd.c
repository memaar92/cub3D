/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:48:27 by mamesser          #+#    #+#             */
/*   Updated: 2023/05/18 10:41:25 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_abs2(int n)
{
	if (n < 0)
		n = -n;
	return (n);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
		ft_putchar_fd('-', fd);
	if (n > 9 || n < -9)
	{
		ft_putnbr_fd(ft_abs2(n / 10), fd);
		ft_putnbr_fd(ft_abs2(n % 10), fd);
	}
	else
		ft_putchar_fd(ft_abs2(n) + '0', fd);
}
