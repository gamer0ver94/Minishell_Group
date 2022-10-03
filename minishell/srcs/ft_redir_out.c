/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 12:31:03 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/03 14:35:38 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redirect_out(t_execc *exe, t_command **prompt, char **envp)
{
	t_command *tmp2;
	int file;
	tmp2 = exe->tmp;
	if (fork() == 0)
	{	
		while (tmp2->meta_char && !ft_strncmp(tmp2->meta_char, ">", 1))
		{
			if (file)
				close(file);
			if (access(tmp2->next->argv[0], F_OK) == 0 \
				&& !ft_strncmp(tmp2->meta_char, ">>", 2))
				file = open(tmp2->next->argv[0], O_RDWR | O_APPEND);
			else if (access(tmp2->next->argv[0], F_OK) == 0 \
				&& !ft_strncmp(tmp2->meta_char, ">", 1))
				file = open(tmp2->next->argv[0], O_RDWR | O_TRUNC);
			else
			{
				file = open(tmp2->next->argv[0], O_RDWR | O_CREAT, 0777);
			}
					
			exe->h++;
			tmp2 = tmp2->next;
			write(2, & exe->h,4);
		}
		if (get_last_meta((*prompt), exe->tmp) && !ft_strncmp(get_last_meta((*prompt), exe->tmp), "|", 1))
		{
			dup2(exe->fd[exe->i - 1][0], STDIN_FILENO);
		}
		dup2(file, STDOUT_FILENO);
		close_files(prompt, exe->files);
		close_pipes(prompt, exe->fd);
		exec_simple(exe->tmp, envp);
		exit(0);
	}
	exe->i++;
	while (exe->tmp->next && !ft_strncmp(exe->tmp->meta_char, ">", 1))
		exe->tmp = exe->tmp->next;
}