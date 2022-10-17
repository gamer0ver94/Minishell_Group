/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_complex_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:10:00 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/13 14:21:14 by dpaulino         ###   ########.fr       */
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
		if (tmp->meta_char && !ft_strncmp(tmp->meta_char, "|", 1))
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void	free_fd(t_execc *exe, t_command **prompt)
{
	int	i;

	i = 0;
	(void)prompt;
	while (i < count_pipes(prompt))
	{
		free(exe->fd[i]);
		i++;
	}
	if (exe->fd)
		free(exe->fd);
}

void	alloc_fd(t_execc *exe, t_command **prompt)
{
	int	i;

	i = 0;
	(void)prompt;
	exe->fd = malloc(sizeof(int *) * count_pipes(prompt));
	while (i < count_pipes(prompt))
	{
		exe->fd[i] = malloc(sizeof(int) * 2);
		if (!exe->fd[i])
			printf("error alocation mem\n");
		i++;
	}
}

void	open_pipes(t_command **prompt, int **fd)
{
	int	i;

	i = 0;
	while (i < count_pipes(prompt))
	{
		if (pipe(fd[i]) == -1)
			write(2, "error opening pipe\n", 19);
		i++;
	}
}

void	close_pipes(t_command **prompt, int **fd)
{
	int	i;

	i = 0;
	(void)prompt;
	while (i < count_pipes(prompt))
	{
		if (close(fd[i][0]) == -1)
			write(2, "error opening pipe\n", 19);
		if (close(fd[i][1]) == -1)
			write(2, "error opening pipe\n", 19);
		i++;
	}
}
