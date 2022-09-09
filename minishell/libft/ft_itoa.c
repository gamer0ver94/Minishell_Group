/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:08:22 by dpaulino          #+#    #+#             */
/*   Updated: 2022/03/19 17:40:29 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*convert(char *str, int counted, int n)
{
	if (n == -2147483648)
	{	
		n = -147483648;
		str[1] = '2';
	}
	str[counted] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	if (n == 0)
		str[0] = '0';
	while (n > 0)
	{
		str[counted - 1] = (n % 10) + '0';
		counted--;
		n = n / 10;
	}
	return (str);
}

static int	digitcount(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		return (11);
	}
	if (n == 0)
	{
		return (1);
	}
	if (n < 0)
	{
		count++;
		n = n * (-1);
	}
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		counted;

	counted = digitcount(n);
	str = malloc(sizeof(char) * counted + 1);
	if (!str)
		return (NULL);
	convert(str, counted, n);
	return (str);
}
