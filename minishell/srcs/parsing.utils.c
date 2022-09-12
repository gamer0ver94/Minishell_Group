/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 14:30:06 by dpaulino          #+#    #+#             */
/*   Updated: 2022/09/08 17:49:05 by dpaulino         ###   ########.fr       */
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

int	find_char(char *buffer, char c)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == c)
			return (1);
		i++;
	}
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

// void	get_dolar_var(t_command **prompt, char **arg, char *tmp, char **envp)
// {
// 	int	i;

// 	i = 0;
// 	while((*prompt)->envp[i])
// 	{
// 		printf("HHHHHH%s\n",*arg);
// 		if (!ft_strncmp(tmp, envp[i], ft_strlen(tmp)))
// 		{
// 			if(!**arg)
// 				*arg = ft_strjoin(*arg,envp[i] + ft_strlen((*prompt)->envp[i]));
// 		}
// 		i++;
// 	}
// } 

void	get_dolar_char(t_command **prompt, char **arg, int i)
{
	int k = 0;
	int		j;
	char	*tmp;
	int h = 0;
	(void)prompt;
	j = 0;

	while (arg[i])
	{
		if (arg[i][k] == '$')
		{
			tmp = ft_calloc(100, sizeof(tmp));
			while (arg[i][k + 1] && (arg[i][k + 0] != '$' || arg[i][k + 1] != ' '))
			{
				tmp[j] = arg[i][k + 1];
				j++;
				k++;
			}
			tmp[j] = '\0';
			while ((*prompt)->envp[h])
			{
				if (!ft_strncmp(tmp, (*prompt)->envp[h], ft_strlen(tmp)))
				{
					arg[i] = ft_strdup((*prompt)->envp_val[h]);
					h = 0;
					break;
				}
				h++;
			}
		}
		j = 0;
		i++;
		if (*tmp)
			free(tmp);
	}
}

void	identify_dolar(t_command **prompt, char **args)
{
	int	i;

	(void)prompt;
	i = 0;
	while (args[i])
	{
		if (find_char(args[i], '$'))
			get_dolar_char(prompt, args, i);
		i++;
	}
}
