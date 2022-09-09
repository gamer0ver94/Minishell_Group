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
	int i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void replace_dolar(t_command **prompt, char **args, char **envp)
{
	int	i;
	int	j;
	int g;
	int h;
	int	l;
	char *tmp;
	char **string;
	int x = 0;
	string = ft_calloc(50, sizeof(char *));
	l = 0;
	tmp = ft_calloc(50, sizeof(char));
	g = 1;
	(void)envp;
	j = 0;
	i = 0;
	h = 0;
	while (args[i])
	{
		while (args[i][j])
		{
			if (args[i][j] == '$')
			{
				while (args[i][j + g] && args[i][j + g] != ' ')
				{
					tmp[h] = args[i][j + g];
					g++;
					h++;
				}
				tmp[h] = '\0';
				h = 0;
				while ((*prompt)->envp && (*prompt)->envp[h])
				{
					if (!ft_strncmp(tmp, (*prompt)->envp[h], ft_strlen(envp[h])))
					{
						while (envp[h][l] != '=')
							l++;
						l++;
						if (j > 0)
						{	
							string[x] = ft_calloc(50, sizeof(char));
							ft_strlcpy(string[x++], args[i], j + 1);
							string[x++] = ft_strdup(envp[h] + l);
							if (args[i][j + g])
							{
								string[x++] = ft_strdup(args[i] + j + g -1);
								printf("%s",string[x - 1]);
							}
							string[x] = NULL;
							x = 0;
							ft_bzero(args[i], ft_strlen(args[i]));
							while (string[x])
							{
								args[i] = ft_strjoin(args[i], string[x++]);
							}
						}
						else if (args[i][j + 1])
						{
							args[i] = ft_strjoin(envp[h] + l, args[i] + j + g);//prob bug
							if (find_char(args[i], '$'))
								replace_dolar(prompt,args, envp);
						}
						else
							args[i] = ft_strdup(envp[h] + l);
						break ;
					}
					else
						h++;
				}
				if(!(*prompt)->envp[h])
					ft_strlcpy(args[i], args[i], j + 1);
			}
			j++;
		}
		j = 0;
		i++;
	}
}
