/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_meta_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 21:32:24 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/24 15:00:38 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_meta_chars(t_command **prompt, t_helper2 *buf_s)
{
	t_command	*tmp;
	int			i;

	i = 0;
	tmp = (*prompt);
	while (tmp)
	{
		if (buf_s->meta_chars[i])
		{
			if (tmp->meta_char)
				free(tmp->meta_char);
			tmp->meta_char = ft_strdup(buf_s->meta_chars[i]);
		}
		else
			tmp->meta_char = NULL;
		i++;
		tmp = tmp->next;
	}
}

int	find_meta_char(char *buffer)
{
	int	i;
	int	lock;

	lock = 0;
	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\"' || buffer[i] == '\'')
		{
			lock++;
			if (lock == 2)
				lock = 0;
			i++;
		}
		else if (lock == 0)
		{
			if (buffer[i] == '<' || buffer[i] == '|' || buffer[i] == '>')
				return (1);
			i++;
		}
		else
			i++;
	}
	return (0);
}

void	meta_char_utils(t_tmp *tp, char *buffer, t_helper2 *buf_s)
{
	buf_s->meta_chars[tp->a] = ft_calloc(2000, sizeof(char));
	while (buffer [tp->i] == '<' || \
		buffer [tp->i] == '>' || buffer [tp->i] == '|')
	{
		buf_s->meta_chars[tp->a][tp->b] = buffer[tp->i];
		tp->b++;
		tp->i++;
	}
	tp->a++;
	tp->j++;
	tp->h = 0;
	tp->b = 0;
	buf_s->exe[tp->j] = ft_calloc(100, sizeof(char));
	if (buffer[tp->i] == ' ')
		tp->i++;
}

void	init_meta_struct(t_tmp *help)
{
	help->i = 0;
	help->j = 0;
	help->h = 0;
	help->a = 0;
	help->b = 0;
}

void	parse_meta_chars(char *buffer, t_helper2 *buf_s)
{
	t_tmp	tp;
	int		i;
	int		lock;

	lock = 0;
	i = 0;
	init_meta_struct(&tp);
	buf_s->exe[tp.j] = ft_calloc(100, sizeof(char));
	while (buffer[i] == ' ')
		i++;
	while (buffer[tp.i])
	{
		meta_char_util2(buffer, &lock, buf_s, &tp);
	}
	buf_s->exe[tp.j + 1] = NULL;
	buf_s->meta_chars[tp.a] = NULL;
}
