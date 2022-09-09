/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 03:36:54 by marvin            #+#    #+#             */
/*   Updated: 2022/03/09 16:23:31 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	l;

	l = n;
	if (l < 0)
	{
		l = l * -1;
		write (fd, "-", 1);
	}
	if (l == -2147483648)
	{
		ft_putchar_fd('2', fd);
		l = 147483648;
	}
	if (l > 9)
	{
		ft_putnbr_fd(l / 10, fd);
		ft_putchar_fd((l % 10) + '0', fd);
	}
	else
	{
		ft_putchar_fd(l + '0', fd);
	}
}
