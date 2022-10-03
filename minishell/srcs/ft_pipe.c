/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 12:31:43 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/03 10:37:37 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pipef(t_execc *exe, t_command **prompt, char **envp)
{
	if (fork() == 0)
	{
		if (exe->tmp->id == 1)
			dup2(exe->fd[exe->i][1], STDOUT_FILENO);
		else
		{
			dup2(exe->fd[exe->i - 1][0], STDIN_FILENO);
			dup2(exe->fd[exe->i][1], STDOUT_FILENO);
		}
		close_pipes(prompt, exe->fd);
		exec_simple(exe->tmp, envp);
		exit(0);
	}
	exe->tmp = exe->tmp->next;
}

void	last_cmd(t_execc *exe, t_command **prompt, char **envp)
{
	(void)prompt;
	(void)(envp);
	if (!ft_strncmp(get_last_meta((*prompt), exe->tmp), "|", 1))
	{
		if (fork() == 0)
		{
			dup2(exe->fd[exe->i - 1][0], STDIN_FILENO);
			close_pipes(prompt, exe->fd);
			exec_simple(exe->tmp, envp);
			exit (0);
		}
	}
	exe->tmp = exe->tmp->next;
}
