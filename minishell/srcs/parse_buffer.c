/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 13:34:36 by dpaulino          #+#    #+#             */
/*   Updated: 2022/09/08 15:36:06 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_commands(char **split, t_command **prompt)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	(*prompt)->cmd = ft_strdup(split[0]);
	(*prompt)->argc = ft_array_size(split);
	(*prompt)->argv = ft_calloc((*prompt)->argc + 1, sizeof(char *));
	while (split && split[i])
	{
			(*prompt)->argv[j] = ft_strdup(split[i]);
			j++;
			i++;
	}
	(*prompt)->argv[j] = NULL;
}

int	split_buffer(char **args, char *buffer)
{
	t_parse	p;
	int code;

	code = 0;
	init_parse_struct(&p);
	args[p.i] = ft_calloc(100, sizeof(char));
	while (buffer[p.l])
	{
		if ((buffer[p.l] == '\"') && (p.lock_2 != 1) && (p.lock != 2))
		{
			p.lock++;
			if (p.lock == 2)
				p.lock = 0;
		}
		else if ((buffer[p.l] == '\'') && (p.lock_2 != 2) && (p.lock != 1))
		{
			p.lock_2++;
			if (p.lock_2 == 2)
				p.lock_2 = 0;
		}
		else if ((buffer[p.l] == ' ') && (p.lock != 1 && p.lock_2 != 1))
		{
			p.i++;
			p.j = 0;
			args[p.i] = ft_calloc(100, sizeof(char));
			while (buffer[p.l] && buffer[p.l + 1] == ' ')
				p.l++;
		}
		else if ((buffer[p.l] == ' ') && (p.lock == 1 || p.lock_2 == 1))
		{
			args[p.i][p.j++] = buffer[p.l];
			if (buffer[p.l] == '$' && p.lock_2 == 0)
				code++;
		}
		else
		{
			args[p.i][p.j++] = buffer[p.l];
			if (buffer[p.l] == '$' && p.lock_2 == 0)
				code++;
		}
		p.l++;
	}
	return (code);
}

int	parse_buffer(char *buffer, t_command **prompt, char **envp)
{
	char	**args;
	int		code;
	code = 0;
	args = ft_calloc(100, sizeof(char *));
	if (!args)
		return (1);
	if (find_char(buffer, '|'))
	{
		args = ft_split(buffer, '|');
		return (1);
	}
	else
	{
		code = split_buffer(args, buffer);
		if (find_char(buffer, '$'))
		{
			if (code > 0)
				replace_dolar(prompt, args, envp);
		}
		get_commands(args, prompt);
		free_args(args);
	}
	return (0);
}

	// if(p.lock == 1) //if quotes are open in the end of the parsing
	// {
	// 	args[p.i] = NULL;
	// 	free(args[p.i]);
	// 	printf("double quotes not closed\n");
	// 	//open a new prompt
	// 	while (1)
	// 		readline("> ");
	// }
	// args[p.j] = NULL;