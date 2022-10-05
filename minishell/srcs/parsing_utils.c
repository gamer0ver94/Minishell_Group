/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 14:30:06 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/05 12:50:31 by memam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_parse_struct(t_parse *p)
{
	p->i = 0;
	p->j = 0;
	p->l = 0;
	p->lock = 0;
	p->lock_2 = 0;
	p->code = 0;
}

int	ft_array_size(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int	find_char(char *buffer, char *c)
{
	char	*str;
	size_t	size;
	size_t	i;
	char	*tmp;

	i = 0;
	size = ft_strlen(c);
	str = ft_strdup(buffer);
	tmp = str;
	while (i < ft_strlen(buffer) - 1)
	{
		if (!ft_strncmp(str, c, size))
		{
			free(tmp);
			return (1);
		}
		str++;
		i++;
	}
	free(tmp);
	return (0);
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}
