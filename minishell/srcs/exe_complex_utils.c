/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_complex_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:10:00 by dpaulino          #+#    #+#             */
/*   Updated: 2022/09/21 13:36:06 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_pipes(t_command **prompt)
{
	t_command	*tmp;
	int			i;

	i = 0;
	tmp = (*prompt);
	while (tmp)
	{
		if (tmp->meta_char)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void	free_fd(t_command **prompt, int **fd)
{
	int	i;

	i = 1;
	while (i < count_pipes(prompt))
	{
		if (fd[i])
			free(fd[i]);
		i++;
	}
	if (fd)
		free (fd);
}

void	open_pipes(t_command **prompt, int **fd)
{
	int	i;

	i = 0;
	while (i < count_pipes(prompt))
	{
		if (fd)
			fd[i] = malloc(sizeof(int) * 2);
		if (pipe(fd[i]))
			printf("pipe[%d] did not open", i);
		i++;
	}
}

void	close_pipes(t_command **prompt, int **fd)
{
	int	i;

	i = 0;
	while (i < count_pipes(prompt))
	{
		if (fd[i])
		{
			close(fd[i][0]);
			close(fd[i][1]);
		}
		i++;
	}
}

void	init_execc_struct(t_execc *exe, t_command **prompt)
{
	exe->tmp = (*prompt);
	exe->lock = 0;
	exe->j = count_pipes(prompt);
	exe->i = 0;
	exe->fd = malloc(sizeof(int) * count_pipes(prompt));
	open_pipes(prompt, exe->fd);
}
