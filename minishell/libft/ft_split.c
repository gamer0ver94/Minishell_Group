/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 10:59:19 by dpaulino          #+#    #+#             */
/*   Updated: 2022/08/29 17:03:58 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	wordcount(char const *s, char c)
{
	size_t	j;
	int		i;

	j = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
		{
			i++;
		}
		while (s[i] != c && s[i] != 0)
		{
			if (s[i + 1] == c || s[i + 1] == 0)
			{
				j++;
			}
			i++;
		}
	}
	return (j);
}

static char	**wordalloc(char **str, char const *s, char c)
{
	size_t	count;
	int		i;
	int		h;

	count = 0;
	i = 0;
	h = 0;
	while (s[h])
	{
		if (s[h] != c)
			count++;
		else if (h > 0 && s[h - 1] != c)
		{
			str[i] = malloc(sizeof(char) * (count + 1));
			if (!str[i])
				return (0);
			count = 0;
			i++;
		}
		if (s[h + 1] == '\0' && s[h] != c)
		str[i] = malloc(sizeof(char) * count + 1);
		h++;
	}
	return (str);
}

static char	**wordcpy(char **str, char const *s, char c)
{
	int	i;
	int	j;
	int	h;

	i = 0;
	j = 0;
	h = 0;
	while (s[h])
	{
		if (s[h] != c)
			str[i][j++] = s[h];
		else if (h > 0 && s[h - 1] != c)
		{
			if (h != 0)
			{
				str[i][j] = '\0';
				j = 0;
				i++;
			}
		}
		if (s[h + 1] == '\0' && s[h] != c)
			str[i][j] = '\0';
		h++;
	}
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		words;

	if (!s || !*s)
	{
		str = malloc(sizeof(char *) * 1);
		if (!str)
			return (NULL);
		*str = 0;
		return (str);
	}
	words = wordcount(s, c);
	str = malloc(sizeof(char *) * (words + 1));
	if (!str)
		return (0);
	if (wordalloc(str, s, c) != 0)
		wordcpy(str, s, c);
	else
	{
		free(str);
		return (NULL);
	}
	str[words] = 0;
	return (str);
}
