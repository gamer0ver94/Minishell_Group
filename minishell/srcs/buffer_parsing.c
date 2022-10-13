/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 13:34:36 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/13 12:44:23 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_commands(char **split, t_command **prompt, char **envp)
{
	t_command	*tmp;
	int			i;
	int			j;

	tmp = (*prompt);
	j = 0;
	i = 0;
	if ((*prompt)->argc != 0)
	{
		struct_init_complex(&tmp, envp);
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->cmd = ft_strdup(split[0]);
	tmp->argv = ft_calloc(500, sizeof(char *));
	while (split && split[i])
	{
		if (split[i][0])
			tmp->argv[j++] = ft_strdup(split[i++]);
		else
			i++;
	}
	tmp->argc = j;
	tmp->argv[j] = NULL;
}

void	parse_quotes_util(t_parse *p, char **args, char *buffer)
{
	if ((buffer[p->l] == '\"') && (p->lock_2 != 1) && (p->lock++ != 2))
		double_quotes(p, args, buffer);
	else if ((buffer[p->l] == '\'') && (p->lock_2 != 2) && (p->lock != 1))
	{
		p->lock_2++;
		if (p->lock_2 == 2)
			p->lock_2 = 0;
		p->l++;
	}
	else if (buffer[p->l] == ' ' && p->lock != 1 && p->lock_2 != 1)
	{
		jump_spaces(p, args, buffer);
	}
	else
	{
		if (buffer[p->l] == '$' && p->lock_2 != 1)
		{
			args[p->i][p->j++] = '&';
		}
		else
			args[p->i][p->j++] = buffer[p->l];
		p->l++;
	}
}

int	parse_quotes(char **args, char *buffer)
{
	t_parse	*p;

	p = malloc(sizeof(t_parse));
	init_parse_struct(p);
	args[p->i] = ft_calloc(100, sizeof(char));
	while (buffer[p->l])
	{
		parse_quotes_util(p, args, buffer);
	}
	free(p);
	return (0);
}

int	buffer_parsing(char *buffer, t_command **prompt, char **envp)
{
	t_helper2	*buf_s;

	buf_s = malloc(sizeof(t_helper));
	buf_s->exe = malloc(sizeof(char *) * 50);
	buf_s->meta_chars = malloc(sizeof(char *) * 50);
	buf_s->i = 0;
	buf_s->code = 0;
	if (find_meta_char(buffer))
	{
		parse_phase_one(buf_s, prompt, buffer, envp);
		free_matrix(buf_s->meta_chars);
		free_matrix(buf_s->exe);
		free(buf_s);
		return (1);
	}
	else
	{
		parse_without_meta(buf_s, buffer, prompt, envp);
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