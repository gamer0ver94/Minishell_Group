/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 16:37:32 by dpaulino          #+#    #+#             */
/*   Updated: 2022/09/21 12:12:50 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_last_meta(t_command *prompt, t_command *tmp)
{
	t_command	*tmp2;

	tmp2 = prompt;
	while (tmp2)
	{
		if (tmp2->next && tmp2->next->id == tmp->id)
			return (tmp2->meta_char);
		tmp2 = tmp2->next;
	}
	return (NULL);
}

void	redirect_out(t_execc *exe, t_command **prompt, char **envp)
{
	int file;
	if (fork() == 0)
	{
		dup2(exe->fd[exe->i][0], STDIN_FILENO);
		file = open(exe->tmp->next->argv[0], O_RDWR | O_CREAT, 0777);
		dup2(file, STDOUT_FILENO);
		close_pipes(prompt, exe->fd);
		close(file);
		exec_simple(exe->tmp, envp);
		exit(0);
	}
	exe->tmp = exe->tmp->next->next;
	exe->i++;
}

void	pipef(t_execc *exe, t_command **prompt, char **envp)
{
	if (fork() == 0)
	{
		dup2(exe->fd[exe->i][0], STDIN_FILENO);
		exe->i++;
		dup2(exe->fd[exe->i][1], STDOUT_FILENO);
		close_pipes(prompt, exe->fd);
		exec_simple(exe->tmp, envp);
		exit(0);
	}
	exe->i++;
	exe->tmp = exe->tmp->next;
}

void	last_cmd(t_execc *exe, t_command **prompt, char **envp)
{
	int 	file;
	if (!ft_strncmp(get_last_meta((*prompt), exe->tmp), "|", 1))
	{
		if (fork() == 0)
		{
			dup2(exe->fd[exe->i][0], STDIN_FILENO);
			close_pipes(prompt, exe->fd);
			exec_simple(exe->tmp, envp);
			exit (0);
		}
	}
	else
	{
		if (access(exe->tmp->argv[0], F_OK) == 0)
			printf("This File exists\n");
		else
		{
			if(fork() == 0)
			{
				file = open(exe->tmp->argv[0], O_RDWR | O_CREAT, 0777);
				dup2(file, STDOUT_FILENO);
				close_pipes(prompt,exe->fd);
				close(file);
				exit(0);
			}
		}
	}

	exe->tmp = exe->tmp->next;
}

void	first_cmd(t_execc *exe, t_command **prompt, char **envp)
{
	int file;
	if (fork() == 0)
	{
		if (!ft_strncmp(exe->tmp->meta_char, ">", 1))
		{
			file = open(exe->tmp->next->argv[0], O_RDWR | O_CREAT, 0777);
			dup2(file, STDOUT_FILENO);
			close(file);
		}
		else
			dup2(exe->fd[exe->i][1], STDOUT_FILENO);
		close_pipes(prompt, exe->fd);
		exec_simple(exe->tmp, envp);
		exit(0);
	}
	if (!ft_strncmp(exe->tmp->meta_char, ">", 1))
		exe->tmp = exe->tmp->next;
	exe->tmp = exe->tmp->next;
}