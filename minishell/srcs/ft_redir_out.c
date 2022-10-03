/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 12:31:03 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/03 10:38:15 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redirect_out(t_execc *exe, t_command **prompt, char **envp)
{
	t_command *tmp2;

	tmp2 = exe->tmp;
	if (fork() == 0)
	{	
		while (tmp2->meta_char && !ft_strncmp(tmp2->meta_char, ">", 1))
		{
			if (access(tmp2->next->argv[0], F_OK) == 0 \
				&& !ft_strncmp(tmp2->meta_char, ">>", 2))
				exe->fd[exe->i + 1][1] = open(tmp2->next->argv[0], O_RDWR | O_APPEND);
			else if (access(tmp2->next->argv[0], F_OK) == 0 \
				&& !ft_strncmp(tmp2->meta_char, ">", 1))
				exe->fd[exe->i + 1][1] = open(tmp2->next->argv[0], O_RDWR | O_TRUNC);
			else
				exe->fd[exe->i + 1][1] = open(tmp2->next->argv[0], O_RDWR | O_CREAT, 0777);
			exe->i++;
			tmp2 = tmp2->next;
		}
		if (get_last_meta((*prompt), exe->tmp) && !ft_strncmp(get_last_meta((*prompt), exe->tmp), "|", 1))
			dup2(exe->fd[exe->i - 2][0], STDIN_FILENO);
		dup2(exe->fd[exe->i - 1][1], STDOUT_FILENO);
		exec_simple(exe->tmp, envp);
		close_pipes(prompt, exe->fd);
		exit(0);
	}
	exe->i++;
	while (exe->tmp->next && !ft_strncmp(exe->tmp->meta_char, ">", 1))
		exe->tmp = exe->tmp->next;
}