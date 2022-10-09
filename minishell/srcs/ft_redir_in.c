/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 12:31:33 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/09 22:32:33 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

void	redirect_in(t_execc *exe, t_command **prompt, char **envp)
{
	int file;
	if (access(exe->tmp->next->argv[0], F_OK) != 0)
	{
		write(2, "bash : ", 7);
		write (2, exe->tmp->next->argv[0], ft_strlen(exe->tmp->next->argv[0]));
		write (2, " No such file or directory\n", 27);
		g_status = 1;
		exe->tmp = exe->tmp->next;
	}
	else
	{
		if (fork() == 0)
		{
			file = open(exe->tmp->next->argv[0], O_RDONLY);
			dup2(file, STDIN_FILENO);
			if (exe->tmp->next->meta_char)
				dup2(exe->fd[exe->i][1], STDOUT_FILENO);
			close(file);
			close_pipes(prompt, exe->fd);
			exec_simple(exe->tmp, envp);
			free_prompt(prompt);
			exit(0);
		}
		exe->i++;
		exe->tmp = exe->tmp->next;
		if (exe->tmp->meta_char)
			exe->tmp = exe->tmp->next;
	}
}

void redirect_in_complex(t_execc *exe, t_command **prompt, char **envp)
{
	char	*buffer;
	char	*res;
	char	*a;
	int		file[2];

	res = ft_calloc(100, sizeof(res));
	pipe(file);
	(void)prompt;
	(void)envp;
	a = ft_strdup(exe->tmp->next->argv[0]);
	while (1)
	{
		buffer = readline("> ");
		if (!ft_strncmp(buffer, a, ft_strlen(a)))
		{
			free(buffer);
			break ;
		}
		write(file[1], "a\n", 2);
		write(file[1], buffer, ft_strlen(buffer));
		write(file[1], "\n", 1);
		free(buffer);
	}
	if (fork() == 0)
	{
		dup2(file[0], STDIN_FILENO);
		if (exe->tmp->next->meta_char)
			dup2(file[1], STDOUT_FILENO);
		close_pipes(prompt, exe->fd);
		close_files(prompt, exe->files);
		close(file[0]);
		close(file[1]);
		exec_simple(exe->tmp, envp);
		exit(0);
	}
	close(file[0]);
	close(file[1]);
	exe->tmp = exe->tmp->next;
}