/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_complex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:48:05 by dpaulino          #+#    #+#             */
/*   Updated: 2022/09/20 15:48:23 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	wait_childs(t_execc *exe)
{
	while (exe->j-- > 0)
	{
		waitpid(-1, NULL, 0);
	}
}

void	first_cmd(t_execc *exe, t_command **prompt, char **envp)
{
	if (fork() == 0)
	{
		dup2(exe->fd[exe->i][1], STDOUT_FILENO);
		close_pipes(prompt, exe->fd);
		exec_simple(exe->tmp, envp);
		exit(0);
	}
	exe->tmp = exe->tmp->next;
}

void	last_cmd(t_execc *exe, t_command **prompt, char **envp)
{
	int file;

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
			printf("exist\n");
		else
		{
			file = open(exe->tmp->argv[0], O_CREAT | O_WRONLY);
			write(file, "hello", 5);
		}
	}

	exe->tmp = exe->tmp->next;
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

// void	redirect_in(t_execc *exe, t_command **prompt, char **envp)
// {
	
// }
void	redirect_out(t_execc *exe, t_command **prompt, char **envp)
{
	if (fork() == 0)
	{
		dup2(exe->fd[exe->i][0], STDIN_FILENO);
		close_pipes(prompt, exe->fd);
		exec_simple(exe->tmp, envp);
		exit(0);
	}
	exe->tmp = exe->tmp->next;
}

void	exec_complex(t_command **prompt, char **envp)
{
	t_execc		exe;

	init_execc_struct(&exe, prompt);
	(void)envp;
	while (exe.tmp)
	{
		if (exe.tmp->id == 1)
		{
			printf("<first i pipe fd in STDOUT>\n");
			first_cmd(&exe, prompt, envp);
		}
		else if (exe.tmp->meta_char && !ft_strncmp(exe.tmp->meta_char, "|", 1))
		{
			printf("<now i know there is a | after, so i will fd STDIN THEN STDOUT>\n");
			pipef(&exe, prompt, envp);
		}
		else if (exe.tmp->meta_char && !ft_strncmp(exe.tmp->meta_char, ">", 1))
			printf("<now i will STDIN and verify if file exist and pipe into the file descriptor>\n");
		else if (exe.tmp->meta_char && !ft_strncmp(exe.tmp->meta_char, ">>", 1))
			printf("<now i will STDIN and verify if file exist and pipe into the file descriptor>\n");
		else if (exe.tmp->meta_char && !ft_strncmp(exe.tmp->meta_char, "<", 1))
			printf("<now i will STDIN and verify if file exist and pipe into the file descriptor>\n");
		else if (exe.tmp->meta_char && !ft_strncmp(exe.tmp->meta_char, "<<", 1))
			printf("<now i will STDIN and verify if file exist and pipe into the file descriptor>\n");
		else
		{
			printf("<now there is no meta char i need to know what is behind this list so i can take a decision>\n");
			last_cmd(&exe, prompt, envp);
		}
	}
	close_pipes(prompt, exe.fd);
	free_fd(prompt, exe.fd);
	wait_childs(&exe);
}