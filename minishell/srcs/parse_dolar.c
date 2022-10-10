/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dolar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 21:31:03 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/10 12:53:01 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

char *ft_realoc(char *str, int size)
{
	int	i;
	char *tmp;
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

char	*get_dolar_var(char *tmp2, t_command **prompt)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!ft_strncmp(tmp2, "?", 1))
	{
		tmp = ft_itoa(g_status);
		return (tmp);
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
				tmp = ft_strdup((*prompt)->envp_val[i]);
				tmp[ft_strlen(tmp)] = '\0';
				return (tmp);
			}
			i++;
		}
	}
	tmp = ft_calloc(1, sizeof(char));
	return (tmp);
}

void	get_dolar_char(t_command **prompt, char **arg, int i)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*var;
	int		h;
	int	size;
	char	*p;

	size = 0;
	h = 0;
	(void)prompt;
	tmp = ft_calloc(200, sizeof(char));
	j = 0;
	while (arg[i] && arg[i][j])
	{
		if (arg[i][j] == '&' )
		{
			j++;
			tmp2 = ft_calloc(100, sizeof(tmp));
			while ((arg[i][j] && arg[i][j] != '&') && (arg[i][j] != '$') \
				&& (arg[i][j]) && (arg[i][j] != ' '))
				tmp2[h++] = arg[i][j++];
			h = 0;
			p = get_dolar_var(tmp2, prompt);
			var = ft_strjoin(tmp, p);
			free(p);
			free(tmp2);
			free(tmp);
			tmp = ft_strdup(var);
			free(var);
			size = ft_strlen(tmp);
		}
		else
		{
			tmp = ft_realoc(tmp, 200);
			tmp[size] = arg[i][j];
			size++;
			j++;
		}
	}
	free(arg[i]);
	arg[i] = ft_strdup(tmp);
	free(tmp);
}

void	identify_dolar(t_command **prompt, char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
	{
		if (args[i][0] && find_char(args[i], "&"))
			get_dolar_char(prompt, args, i);
		i++;
	}
}
