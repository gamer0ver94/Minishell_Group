/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 12:31:43 by dpaulino          #+#    #+#             */
/*   Updated: 2022/09/30 14:53:52 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pipef(t_execc *exe, t_command **prompt, char **envp)
{
	if (fork() == 0)
	{
		if (exe->tmp->id == 1)
			dup2(exe->fd[exe->i][1], STDOUT_FILENO);
		dup2(exe->fd[exe->i][0], STDIN_FILENO);
		exe->i++;
		if(exe->tmp->meta_char)
			dup2(exe->fd[exe->i + 1][1], STDOUT_FILENO);
		close_pipes(prompt, exe->fd);
		exec_simple(exe->tmp, envp);
		exit(0);
	}
	exe->i++;
	exe->tmp = exe->tmp->next;
}