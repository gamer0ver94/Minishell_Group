/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:19:39 by dpaulino          #+#    #+#             */
/*   Updated: 2022/03/09 16:31:13 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *string)
{
	char	*newstr;
	size_t	i;
	size_t	size;

	size = ft_strlen(string);
	i = 0;
	newstr = (char *)malloc(sizeof(char) * size + 1);
	if (!newstr)
	{
		return (NULL);
	}
	while (i < size)
	{
		newstr[i] = string[i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}
