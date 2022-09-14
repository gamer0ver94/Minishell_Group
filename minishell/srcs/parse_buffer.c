/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 13:34:36 by dpaulino          #+#    #+#             */
/*   Updated: 2022/09/14 15:48:11 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_commands(char **split, t_command **prompt, char **envp)
{
	int		i;
	int		j;
	t_command *tmp;
	
	(void)envp;
	tmp = (*prompt);
	j = 0;
	i = 0;
	if ((*prompt)->argc != 0)
	{
		struct_init2(&tmp, envp);
	}
	while(tmp->next != NULL)
		tmp = tmp->next;
	// if (tmp->argc > 0 && tmp->next == NULL)
	// {
		
	// 	// tmp->next = malloc(sizeof(t_command));
	// 	// tmp = tmp->next;
	// 	// tmp->cmd = NULL;
	// 	// tmp->argc = 0;
	// 	// tmp->argv = NULL;
	// 	// tmp->next = NULL;
	// }
	tmp->cmd = ft_strdup(split[0]);
	tmp->argv = ft_calloc(500, sizeof(char *));
	while (split && split[i])
	{
		if (split[i][0])
		{
			tmp->argv[j] = ft_strdup(split[i]);
			j++;
			i++;
		}
		else
			i++;
	}
	tmp->argc = j;
	tmp->argv[j] = NULL;
}

int	split_buffer(char **args, char *buffer)
{
	t_parse	p;
	int		code;

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
	char	**pipes;
	int		code;
	int		i;

	i = 0;
	code = 0;

	if (find_char(buffer, '|'))
	{
		pipes = ft_split(buffer, '|');
		while (pipes[i])
		{
			if (pipes[i][0] == ' ')
				pipes[i]++;
			args = ft_calloc(100, sizeof(char *));
			code = split_buffer(args, pipes[i]);
			if (find_char(pipes[i], '$'))
			{
				if (code > 0)
					identify_dolar(prompt, args);
			}
			get_commands(args, prompt, envp);
			free_args(args);
			i++;
		}
		free(pipes);
		return (1);
	}
	else
	{
		args = ft_calloc(100, sizeof(char *));
		code = split_buffer(args, buffer);
		if (find_char(buffer, '$'))
		{
			if (code > 0)
				identify_dolar(prompt, args);
		}
		get_commands(args, prompt, envp);
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