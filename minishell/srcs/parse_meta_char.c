/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_meta_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 21:32:24 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/05 15:35:54 by dpaulino         ###   ########.fr       */
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
	if (find_char(buffer, "|"))
		return (1);
	else if (find_char(buffer, "<"))
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

void	meta_char_utils(t_tmp *tp, char *buffer, t_helper2 *buf_s)
{
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
	buf_s->meta_chars[tp->a] = ft_calloc(100, sizeof(char));
	//here
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

	init_meta_struct(&tp);
	buf_s->exe[tp.j] = ft_calloc(50, sizeof(char));
	buf_s->meta_chars[tp.a] = ft_calloc(50, sizeof(char));
	while (buffer[tp.i])
	{
		if (buffer [tp.i] == '<' || buffer [tp.i] == '>' || buffer [tp.i] == '|'\
			|| buffer [tp.i] == '&')
		{
			meta_char_utils(&tp, buffer, buf_s);
		}
		else
			buf_s->exe[tp.j][tp.h++] = buffer[tp.i++];
	}
	buf_s->exe[tp.j + 1] = NULL;
	buf_s->meta_chars[tp.a] = NULL;
}
