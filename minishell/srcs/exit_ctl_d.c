/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_ctl_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 23:47:26 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/24 15:05:56 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	meta_char_util2(char *buffer, int *lock, t_helper2 *buf_s, t_tmp *tp)
{
	if (buffer[(*tp).i] == '\"' || buffer[(*tp).i] == '\'')
	{
		(*lock)++;
		if ((*lock) == 2)
			(*lock) = 0;
		buf_s->exe[(*tp).j][(*tp).h++] = buffer[(*tp).i++];
	}
	if ((*lock) == 0 && (buffer [(*tp).i] == '<' || buffer [(*tp).i] == '>' || \
	buffer [(*tp).i] == '|'))
	{
		meta_char_utils(tp, buffer, buf_s);
	}
	else
		buf_s->exe[(*tp).j][(*tp).h++] = buffer[(*tp).i++];
}

void	get_dolar_char(t_command **prompt, char **arg, int i)
{
	t_helper3	*help;

	help = malloc(sizeof(t_helper3));
	init_helper3(help);
	help->i = i;
	while (arg[i] && arg[i][help->j])
	{
		if (arg[i][help->j] == '&' )
			get_dolar_helper(help, prompt, arg);
		else
		{
			help->tmp = ft_realoc(help->tmp, 200);
			help->tmp[help->size] = arg[i][help->j];
			help->size++;
			help->j++;
		}
	}
	free(arg[i]);
	arg[i] = ft_strdup(help->tmp);
	free(help->tmp);
	free(help);
}

void	get_dolar_helper(t_helper3 *help, t_command **prompt, char **arg)
{
	help->j++;
	help->tmp2 = ft_calloc(100, sizeof(help->tmp));
	while ((arg[help->i][help->j] && arg[help->i][help->j] != '&') && \
		(arg[help->i][help->j] != '$') \
		&& (arg[help->i][help->j]) && (arg[help->i][help->j] != ' '))
		help->tmp2[help->h++] = arg[help->i][help->j++];
	help->h = 0;
	help->p = get_dolar_var(help->tmp2, prompt);
	help->var = ft_strjoin(help->tmp, help->p);
	free(help->p);
	free(help->tmp2);
	free(help->tmp);
	help->tmp = ft_strdup(help->var);
	free(help->var);
	help->size = ft_strlen(help->tmp);
}

void	exit_ctl_d(char *buffer, char **envp)
{
	if (!buffer)
		exit_prompt(envp);
	free(buffer);
}
