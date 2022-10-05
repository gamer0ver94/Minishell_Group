/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 21:26:50 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/05 14:47:13 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_id(t_command **prompt)
{
	t_command	*tmp;
	int			i;

	i = 1;
	tmp = (*prompt);
	while (tmp)
	{
		tmp->id = i;
		tmp = tmp->next;
		i++;
	}
}

void	parse_phase_one(t_helper2 *buf_s, t_command **prompt, char *buffer, char **envp)
{
	parse_meta_chars(buffer, buf_s);
	while (buf_s->exe[buf_s->i])
	{
		if (buf_s->exe[buf_s->i][0] == ' ')
			buf_s->exe[buf_s->i]++;
		buf_s->args = ft_calloc(100, sizeof(char *));
		buf_s->code = parse_quotes(buf_s->args, buf_s->exe[buf_s->i]);
		if (find_char(buf_s->exe[buf_s->i], "$"))
		{
			if (buf_s->code > 0)
				identify_dolar(prompt, buf_s->args);
		}
		get_commands(buf_s->args, prompt, envp);
		get_meta_chars(prompt, buf_s);
		free_args(buf_s->args);
		buf_s->i++;
	}
	get_id(prompt);
}