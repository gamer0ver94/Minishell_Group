/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_parsing_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:29:56 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/21 17:25:39 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	double_quotes(t_parse *p, char **args, char *buffer)
{
	p->lock++;
	if (p->lock == 2)
	{
		p->lock = 0;
		if (buffer[p->l] == ' ')
		{
			args[p->i][p->j] = '\0';
			p->i++;
			p->j = 0;
			while (buffer[p->l + 1] && buffer[p->l + 1] == ' ')
			p->l++;
			if (buffer[p->l + 1])
			args[p->i] = ft_calloc(100, sizeof(char));
		}
	}
	p->l++;
}

void	jump_spaces(t_parse *p, char **args, char *buffer)
{
	args[p->i][p->j] = '\0';
	p->i++;
	p->j = 0;
	while (buffer[p->l] && buffer[p->l] == ' ')
		p->l++;
	if (buffer[p->l])
		args[p->i] = ft_calloc(1000, sizeof(char));
}

int	parse_without_meta(t_helper2 *b, char *buf, t_command **pt, char **env)
{
	b->args = ft_calloc(100, sizeof(char *));
	if (parse_quotes(b->args, buf) == -2)
	{
		free_args(b->args);
		free(b->exe);
		free(b->meta_chars);
		free(b);
		return (-2);
	}
	if (find_char(buf, "$"))
		identify_dolar(pt, b->args);
	get_commands(b->args, pt, env);
	get_id(pt);
	free_args(b->args);
	free(b->exe);
	free(b->meta_chars);
	free(b);
	return (0);
}
