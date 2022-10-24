/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_parsing_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:14:30 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/24 16:33:22 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parsing_dolar_helper(char *buffer, t_parse *p, char **args)
{
	if (buffer[p->l] == '$' && p->lock_2 != 1)
	{
		if (!buffer[p->l + 1] || buffer[p->l + 1] == ' ')
			args[p->i][p->j++] = '$';
		else
			args[p->i][p->j++] = '&';
	}
	else
		args[p->i][p->j++] = buffer[p->l];
	p->l++;
}

int	check_last_arg(char *buffer)
{
	int	i;

	i = ft_strlen(buffer) - 1;
	while (i > 0)
	{
		if (buffer[i] == ' ')
			i--;
		else if (buffer[i] == '|' || buffer[i] == '>' || buffer[i] == '<')
			return (0);
		else
			return (1);
	}
	return (0);
}

int	exception(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == ' ')
			i++;
		else if (buffer[i] != '<' && buffer[i] != '>' && buffer[i] != '|')
			return (0);
		else
		{
			g_status = 258;
			write(2, "bash: syntax error near unexpected token\n", 42);
			return (1);
		}
	}
	return (1);
}

int	exception2(char *buffer)
{
	int	i;
	int	j;

	j = 0;
	i = ft_strlen(buffer) - 1;
	while (j < i)
	{
		if (buffer[j] != '\"' && buffer[j] != '\'' && buffer[j] != ' ')
			return (0);
		j++;
	}
	g_status = 127;
	write(2, "bash : command not found\n", 26);
	return (2);
}

int	exception_checker(char *buffer, t_helper2 **buf_s)
{
	if (is_empty_buffer(buffer))
		return (2);
	if (exception(buffer))
		return (2);
	if (exception2(buffer) == 2)
		return (2);
	(*buf_s) = malloc(sizeof(t_helper));
	(*buf_s)->exe = malloc(sizeof(char *) * 50);
	(*buf_s)->meta_chars = malloc(sizeof(char *) * 50);
	(*buf_s)->i = 0;
	(*buf_s)->code = 0;
	return (0);
}
