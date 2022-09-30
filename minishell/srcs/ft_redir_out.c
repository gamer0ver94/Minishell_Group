/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 12:31:03 by dpaulino          #+#    #+#             */
/*   Updated: 2022/09/30 14:50:21 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redirect_out(t_execc *exe, t_command **prompt, char **envp)
{
	int file;
	
	if (fork() == 0)
	{	
		if (access(exe->tmp->next->argv[0], F_OK) == 0 \
				&& !ft_strncmp(exe->tmp->meta_char, ">>", 2))
			file = open(exe->tmp->next->argv[0], O_RDWR | O_APPEND);
		else if (access(exe->tmp->next->argv[0], F_OK) == 0 \
				&& !ft_strncmp(exe->tmp->meta_char, ">", 1))
			file = open(exe->tmp->next->argv[0], O_RDWR | O_TRUNC);
		else
			file = open(exe->tmp->next->argv[0], O_RDWR | O_CREAT, 0777);
		if (exe->tmp->id == 1 && !exe->tmp->next->meta_char)
			dup2(file, STDOUT_FILENO);
		if (exe->tmp->next->next && exe->tmp->next->meta_char)
			dup2(file, STDIN_FILENO);
		close(file);
		close_pipes(prompt, exe->fd);
		exec_simple(exe->tmp, envp);
		exit(0);
	}
	if (exe->tmp->next->next)
		exe->tmp = exe->tmp->next->next;
}