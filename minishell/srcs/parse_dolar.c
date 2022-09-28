/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dolar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 21:31:03 by dpaulino          #+#    #+#             */
/*   Updated: 2022/09/28 16:01:24 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

char	*get_dolar_var(char *tmp2, t_command **prompt)
{
	int	i;

	i = 0;
	if (!ft_strncmp(tmp2, "?", 1))
	{
		tmp2 = ft_strdup(ft_itoa(g_status));
		return(tmp2);
	}
	else
	{
		while ((*prompt)->envp[i])
		{
			if (!ft_strncmp(tmp2, (*prompt)->envp[i], \
				ft_strlen((*prompt)->envp[i])) \
			&& !ft_strncmp(tmp2, (*prompt)->envp[i], ft_strlen(tmp2)))
			{
				ft_bzero(tmp2, ft_strlen(tmp2));
				tmp2 = ft_strdup((*prompt)->envp_val[i]);
				return (tmp2);
			}
			i++;
		}
	}
	
	ft_bzero(tmp2, ft_strlen(tmp2));
	return (tmp2);
}

void	get_dolar_char(t_command **prompt, char **arg, int i)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	int		h;

	h = 0;
	(void)prompt;
	tmp = ft_calloc(100, sizeof(tmp));
	j = 0;
	while (arg[i][j])
	{
		if (arg[i][j++] == '$')
		{
			tmp2 = ft_calloc(100, sizeof(tmp));
			while ((arg[i][j] && arg[i][j] != '$') \
				&& (arg[i][j] && arg[i][j] != ' '))
				tmp2[h++] = arg[i][j++];
			h = 0;
			tmp = ft_strjoin(tmp, get_dolar_var(tmp2, prompt));
			free(tmp2);
		}
		else
			tmp[ft_strlen(tmp)] = arg[i][j];
		if (arg[i][j] != '$')
			j++;
	}
	arg[i] = ft_strdup(tmp);
}

void	identify_dolar(t_command **prompt, char **args)
{
	int	i;

	(void)prompt;
	i = 0;
	while (args[i])
	{
		if (find_char(args[i], "$"))
			get_dolar_char(prompt, args, i);
		i++;
	}
}
