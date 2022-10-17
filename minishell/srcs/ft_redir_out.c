/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 12:31:03 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/15 17:12:06 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	finish_job(t_command **prompt, t_execc *exe, int *file, char **envp)
{
	if (get_last_meta((*prompt), exe->tmp) && \
		!ft_strncmp(get_last_meta((*prompt), exe->tmp), "|", 1))
	{
		dup2(exe->fd[exe->i - 1][0], STDIN_FILENO);
	}
	dup2((*file), STDOUT_FILENO);
	close_files(prompt, exe->files);
	close_pipes(prompt, exe->fd);
	exec_simple(exe->tmp, envp);
	exit(0);
}

void	verify_file(t_command *tmp2, int *file, t_execc *exe)
{
	while (tmp2->meta_char && !ft_strncmp(tmp2->meta_char, ">", 1))
	{
		if ((*file) != 0)
			close((*file));
		if (access(tmp2->next->argv[0], F_OK) == 0 \
			&& !ft_strncmp(tmp2->meta_char, ">>", 2))
			(*file) = open(tmp2->next->argv[0], O_RDWR | O_APPEND);
		else if (access(tmp2->next->argv[0], F_OK) == 0 \
			&& !ft_strncmp(tmp2->meta_char, ">", 1))
			(*file) = open(tmp2->next->argv[0], O_RDWR | O_TRUNC);
		else
			(*file) = open(tmp2->next->argv[0], O_RDWR | O_CREAT, 0777);
		exe->h++;
		tmp2 = tmp2->next;
	}
}

void	redirect_out(t_execc *exe, t_command **prompt, char **envp)
{
	t_command	*tmp2;
	int			file;

	file = 0;
	tmp2 = exe->tmp;
	if (fork() == 0)
	{	
		verify_file(tmp2, &file, exe);
		finish_job(prompt, exe, &file, envp);
	}
	exe->i++;
	while (exe->tmp->next && !ft_strncmp(exe->tmp->meta_char, ">", 1))
		exe->tmp = exe->tmp->next;
}
