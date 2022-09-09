/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:19:23 by dpaulino          #+#    #+#             */
/*   Updated: 2022/03/09 16:14:07 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*tcdest;
	char	*tcsrc;

	if (!src && !dest)
	{
		return (0);
	}
	tcdest = (char *)dest;
	tcsrc = (char *)src;
	i = 0;
	while (i < n)
	{
		tcdest[i] = tcsrc[i];
		i++;
	}
	return (dest);
}
