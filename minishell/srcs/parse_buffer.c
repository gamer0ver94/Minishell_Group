/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 13:34:36 by dpaulino          #+#    #+#             */
/*   Updated: 2022/09/18 21:28:53 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void parse_meta_chars(char *buffer, char **meta_chars, char **exe)
{
	int		i;
	int		j;
	int		h;
	int		a;
	int		b;
	
	i = 0;
	j = 0;
	h = 0;
	a = 0;
	b = 0;
	exe[j] = ft_calloc(50, sizeof(char));
	meta_chars[a] = ft_calloc(50, sizeof(char));
	while (buffer[i])
	{
		if (buffer [i] == '<' || buffer [i] == '>' || buffer [i] == '|'\
			|| buffer [i] == '&')
		{
			while (buffer [i] == '<' || buffer [i] == '>' || buffer [i] == '|'\
			|| buffer [i] == '&')
			{
				meta_chars[a][b] = buffer[i];
				b++;
				i++;
			}
			a++;
			j++;
			h = 0;
			b = 0;
			exe[j] = ft_calloc(100, sizeof(char));
			meta_chars[a] = ft_calloc(100, sizeof(char));
			if (buffer[i] == ' ')
				i++;
		}
		else
		{
			exe[j][h] = buffer[i];
			h++;
			i++;
		}
	}
	exe[j + 1] = NULL;
	meta_chars[a] = NULL;
}

int find_meta_char (char *buffer)
{
	if (find_char(buffer, "|"))
		return (1);
	else if(find_char(buffer, "<"))
		return (1);
	else if (find_char(buffer, "<<"))
		return (1);
	else if (find_char(buffer, ">"))
		return (1);
	else if (find_char(buffer, ">>"))
		return (1);
	else if (find_char(buffer, "&&"))
		return (1);
	else if (find_char(buffer, "||"))
		return (1);
	else
		return (0);
	
}

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

void get_meta_chars(t_command **prompt, char **meta_chars)
{
	t_command *tmp;
	int			i;

	i = 0;
	tmp = (*prompt);
	while (tmp)
	{
		if (meta_chars[i])
			tmp->meta_char = ft_strdup(meta_chars[i]);
		else
			tmp->meta_char = NULL;
		i++;
		tmp = tmp->next;
	}
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

void	get_id(t_command **prompt)
{
	t_command * tmp;
	int i;

	i = 1;
	tmp = (*prompt);
	while (tmp)
	{
		tmp->id = i;
		tmp = tmp->next;
		i++;
	}
}

int	parse_buffer(char *buffer, t_command **prompt, char **envp)
{
	char	**args;
	char	**exe;
	char	**meta_chars;
	int		code;
	int		i;
	exe = malloc(sizeof(char *) * 50);
	meta_chars = malloc(sizeof(char *) * 50);
	i = 0;
	code = 0;

	if (find_meta_char(buffer))
	{
		(void)i;
		parse_meta_chars(buffer, meta_chars, exe);
		while (exe[i])
		{
			if (exe[i][0] == ' ')
				exe[i]++;
			args = ft_calloc(100, sizeof(char *));
			code = split_buffer(args, exe[i]);
			if (find_char(exe[i], "$"))
			{
				if (code > 0)
					identify_dolar(prompt, args);
			}
			get_commands(args, prompt, envp);
			get_meta_chars(prompt, meta_chars);
			free_args(args);
			i++;
		}
		get_id(prompt);
		free(exe);
		return (1);
	}
	else
	{
		args = ft_calloc(100, sizeof(char *));
		code = split_buffer(args, buffer);
		if (find_char(buffer, "$"))
		{
			if (code > 0)
				identify_dolar(prompt, args);
		}
		get_commands(args, prompt, envp);
		get_id(prompt);
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