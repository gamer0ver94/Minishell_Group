/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 16:37:32 by dpaulino          #+#    #+#             */
/*   Updated: 2022/09/28 16:04:37 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int g_status;

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
	int	file;

	if (fork() == 0)
	{	
		if (exe->tmp->id != 1)
			dup2(exe->fd[exe->i][0], STDIN_FILENO);
		if (access(exe->tmp->next->argv[0], F_OK) == 0 \
				&& !ft_strncmp(exe->tmp->meta_char, ">>", 2))
			file = open(exe->tmp->next->argv[0], O_RDWR | O_APPEND);
		else if (access(exe->tmp->next->argv[0], F_OK) == 0 \
				&& !ft_strncmp(exe->tmp->meta_char, ">", 1))
			file = open(exe->tmp->next->argv[0], O_RDWR | O_TRUNC);
		else
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
	exe->tmp = exe->tmp->next;
}

void	first_cmd(t_execc *exe, t_command **prompt, char **envp)
{
	if (!ft_strncmp(exe->tmp->meta_char, ">>", 2) && \
	!ft_strncmp(exe->tmp->meta_char, ">>", ft_strlen(exe->tmp->meta_char)))
		redirect_out(exe, prompt, envp);
	else if (!ft_strncmp(exe->tmp->meta_char, ">", 1) && \
	!ft_strncmp(exe->tmp->meta_char, ">", ft_strlen(exe->tmp->meta_char)))
		redirect_out(exe, prompt, envp);
	else if (!ft_strncmp(exe->tmp->meta_char, "<<", 2) && \
	!ft_strncmp(exe->tmp->meta_char, "<<", ft_strlen(exe->tmp->meta_char)))
		redirect_in_complex(exe, prompt, envp);
	else if (!ft_strncmp(exe->tmp->meta_char, "<", 1) && \
	!ft_strncmp(exe->tmp->meta_char, "<", ft_strlen(exe->tmp->meta_char)))
	{
		redirect_in(exe, prompt, envp);
		exe->tmp = NULL;
	}
	else
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
}

void	redirect_in(t_execc *exe, t_command **prompt, char **envp)
{
	if (access(exe->tmp->next->argv[0], F_OK) != 0)
	{
		write(2, "bash : ", 7);
		write (2, exe->tmp->next->argv[0], ft_strlen(exe->tmp->next->argv[0]));
		write (2, " No such file or directory\n", 27);
		g_status = 1;
	}
	else
	{
		if (fork() == 0)
		{
			exe->fd[exe->i][0] = open(exe->tmp->next->argv[0], O_RDONLY);
			dup2(exe->fd[exe->i][0], STDIN_FILENO);
			close_pipes(prompt, exe->fd);
			exec_simple(exe->tmp, envp);
			exit(0);
		}
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
		write(file[1], buffer, ft_strlen(buffer));
		write(file[1], "\n", 1);
		free(buffer);
	}
	if (fork() == 0)
	{
		dup2(file[0], STDIN_FILENO);
		close_pipes(prompt, exe->fd);
		close(file[0]);
		close(file[1]);
		exec_simple(exe->tmp, envp);
		exit(0);
	}
	close(file[0]);
	close(file[1]);
	exe->tmp = exe->tmp->next;
}
