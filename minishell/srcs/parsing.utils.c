/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 14:30:06 by dpaulino          #+#    #+#             */
/*   Updated: 2022/09/17 01:24:16 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void init_parse_struct(t_parse *p)
{
	p->i = 0;
	p->j = 0;
	p->l = 0;
	p->lock = 0;
	p->lock_2 = 0;
}

int	ft_array_size(char **array) //5
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int	find_char(char *buffer, char *c)
{
	char *str;
	size_t size;
	size_t i;
	char *tmp;

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

void free_args(char **args)//2
{
	int i;
	
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

char	*get_dolar_var(char *tmp2, t_command **prompt)
{
	int i;

	i = 0;
	while ((*prompt)->envp[i])
	{
		if (!ft_strncmp(tmp2, (*prompt)->envp[i], ft_strlen((*prompt)->envp[i])) \
		&& !ft_strncmp(tmp2, (*prompt)->envp[i], ft_strlen(tmp2)))
		{
			ft_bzero(tmp2, ft_strlen(tmp2));
			tmp2 = ft_strdup((*prompt)->envp_val[i]);
			return (tmp2);
		}
		i++;
	}
	ft_bzero(tmp2, ft_strlen(tmp2));
	return (tmp2);
} 

void	get_dolar_char(t_command **prompt, char **arg, int i)
{
	int		j;
	char	*tmp;
	char *tmp2;
	int h = 0;
	(void)prompt;
	tmp = ft_calloc(100,sizeof(tmp));
	
	j = 0;

	while (arg[i][j])
	{
		if (arg[i][j] == '$')
		{
			j++;
			tmp2 = ft_calloc(100,sizeof(tmp));
			while ((arg[i][j] && arg[i][j] != '$') && (arg[i][j] && arg[i][j] != ' '))
			{
				tmp2[h] = arg[i][j];
				h++;
				j++;
			}
			h = 0;
			tmp = ft_strjoin(tmp, get_dolar_var(tmp2, prompt));
			free(tmp2);
		}
		else
			tmp[ft_strlen(tmp)] = arg[i][j];
		if (arg[i][j] != '$')
			j++;
	}
	// free(arg[i]);
	arg[i] = ft_strdup(tmp);
	// free(tmp);
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
