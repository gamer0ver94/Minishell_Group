/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dolar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 21:31:03 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/14 10:10:13 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

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

char	*get_dolar_var(char *tmp2, t_command **prompt)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!ft_strncmp(tmp2, "?", 1))
		return (ft_itoa(g_status));
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

void	init_helper3(t_helper3 *help)
{
	help->size = 0;
	help->h = 0;
	help->tmp = ft_calloc(200, sizeof(char));
	help->j = 0;
}

void	get_dolar_helper(t_helper3 *help, t_command **prompt, char **arg)
{
	help->j++;
	help->tmp2 = ft_calloc(100, sizeof(help->tmp));
	while ((arg[help->i][help->j] && arg[help->i][help->j] != '&') && \
		(arg[help->i][help->j] != '$') \
		&& (arg[help->i][help->j]) && (arg[help->i][help->j] != ' '))
		help->tmp2[help->h++] = arg[help->i][help->j++];
	help->h = 0;
	help->p = get_dolar_var(help->tmp2, prompt);
	help->var = ft_strjoin(help->tmp, help->p);
	free(help->p);
	free(help->tmp2);
	free(help->tmp);
	help->tmp = ft_strdup(help->var);
	free(help->var);
	help->size = ft_strlen(help->tmp);
}

void	get_dolar_char(t_command **prompt, char **arg, int i)
{
	t_helper3	*help;

	help = malloc(sizeof(t_helper3));
	init_helper3(help);
	help->i = i;
	while (arg[i] && arg[i][help->j])
	{
		if (arg[i][help->j] == '&' )
			get_dolar_helper(help, prompt, arg);
		else
		{
			help->tmp = ft_realoc(help->tmp, 200);
			help->tmp[help->size] = arg[i][help->j];
			help->size++;
			help->j++;
		}
	}
	free(arg[i]);
	arg[i] = ft_strdup(help->tmp);
	free(help->tmp);
	free(help);
}
