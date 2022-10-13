/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_complex_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:48:31 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/13 14:00:53 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_execc_struct(t_execc *exe, t_command **prompt)
{
	exe->tmp = (*prompt);
	exe->lock = 0;
	exe->i = 0;
	exe->h = 0;
	exe->j = count_pipes(prompt);
	exe->g = 0;
	exe->pid = malloc(sizeof(pid_t) * 20);
	alloc_fd(exe, prompt);
	alloc_files(exe, prompt);
	open_pipes(prompt, exe->fd);
	open_files(prompt, exe->files);
}

void	open_files(t_command **prompt, int **file)
{
	int	i;

	i = 0;
	while (i < count_files(prompt))
	{
		if (pipe(file[i]) == -1)
			write(2, "error opening pipe\n", 19);
		i++;
	}
}

void	close_files(t_command **prompt, int **file)
{
	int	i;

	i = 0;
	while (i < count_files(prompt))
	{
		if (close(file[i][0]) == -1)
			write(2, "error opening pipe\n", 19);
		if (close(file[i][1]) == -1)
			write(2, "error opening pipe\n", 19);
		i++;
	}
}

void	alloc_files(t_execc *exe, t_command **prompt)
{
	int	i;

	i = 0;
	exe->files = malloc(sizeof(int *) * count_files(prompt));
	while (count_files(prompt) > i)
	{
		exe->files[i] = malloc(sizeof(int) * 2);
		pipe(exe->files[i]);
		i++;
	}
}

void	free_files(t_execc *exe, t_command **prompt)
{
	int	i;

	i = 0;
	(void)prompt;
	while (i < count_files(prompt) && exe->files[i])
	{
		free(exe->files[i]);
		i++;
	}
	if (exe->files)
		free(exe->files);
}
