/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 13:34:36 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/24 16:32:31 by dpaulino         ###   ########.fr       */
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
	tmp->argv = ft_calloc(2000, sizeof(char *));
	while (split && split[i])
	{
		if (split[i][0])
			tmp->argv[j++] = ft_strdup(split[i++]);
		else
			i++;
	}
	tmp->argc = j;
	tmp->argv[j] = NULL;
	tmp->cmd = ft_strdup(tmp->argv[0]);
}

void	parse_quotes_util(t_parse *p, char **args, char *buffer)
{
	if ((buffer[p->l] == '\"') && (p->lock_2 != 1) && (p->lock != 2))
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
		parsing_dolar_helper(buffer, p, args);
	}
}

int	parse_quotes(char **args, char *buffer)
{
	t_parse	*p;

	p = malloc(sizeof(t_parse));
	init_parse_struct(p);
	args[p->i] = ft_calloc(20000, sizeof(char));
	while (buffer[p->l])
	{
		parse_quotes_util(p, args, buffer);
	}
	if (p->lock == 1 || p->lock_2 == 1)
	{
		free(p);
		return (-2);
	}
	free(p);
	return (0);
}

int	is_empty_buffer(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	buffer_parsing(char *buffer, t_command **prompt, char **envp)
{
	t_helper2	*buf_s;

	buf_s = NULL;
	if (exception_checker(buffer, &buf_s) == 2)
		return (2);
	if (find_meta_char(buffer))
	{
		if (!check_last_arg(buffer))
			return (2);
		parse_phase_one(buf_s, prompt, buffer, envp);
		free_matrix(buf_s->meta_chars);
		free_matrix(buf_s->exe);
		free(buf_s);
		return (1);
	}
	else
	{
		if (parse_without_meta(buf_s, buffer, prompt, envp) == -2)
			return (-2);
	}
	return (0);
}
