/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dolar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 21:31:03 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/24 16:04:27 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_realoc(char *str, int size)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_calloc(size, sizeof(char));
	while (str[i] != '\0')
	{
		tmp[i] = str[i];
		i++;
	}
	free(str);
	return (tmp);
}

char	*get_slash(char *str)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = ft_calloc(150, sizeof(char));
	while (str[i])
	{
		if (str[i] == '/')
		{
			while (str[i])
			{
				tmp[j] = str[i];
				j++;
				i++;
			}
		}
		i++;
	}
	return (tmp);
}

char	*get_remaining2(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_calloc(150, sizeof(char));
	while (str[i] != '/')
	{
		tmp[i] = str[i];
		i++;
	}
	return (tmp);
}

char	*get_dolar_var(char *tmp2, t_command **prompt)
{
	char	*aux;
	int		lock;
	char	*tmp;

	tmp = NULL;
	lock = 0;
	if (find_char(tmp2, "/"))
	{
		aux = get_slash(tmp2);
		tmp2 = get_remaining2(tmp2);
		lock++;
	}
	if (!ft_strncmp(tmp2, "?", 1))
		return (ft_itoa(g_status));
	else
	{
		tmp = dolar_utils2(tmp2, aux, &lock, prompt);
	}
	return (tmp);
}

void	init_helper3(t_helper3 *help)
{
	help->size = 0;
	help->h = 0;
	help->tmp = ft_calloc(200, sizeof(char));
	help->j = 0;
}
