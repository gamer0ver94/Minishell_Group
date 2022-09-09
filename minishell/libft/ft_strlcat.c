/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:19:47 by dpaulino          #+#    #+#             */
/*   Updated: 2022/03/09 16:36:06 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	j;
	size_t	dlenght;

	j = 0;
	dlenght = ft_strlen(dest);
	if (size <= dlenght)
	{
		return (size + ft_strlen(src));
	}
	while (dlenght + 1 < size && src[j] != 0)
	{
		dest[dlenght] = src[j];
		dlenght++;
		j++;
	}
	dest[dlenght] = 0;
	return (ft_strlen(dest) + ft_strlen(&src[j]));
}
