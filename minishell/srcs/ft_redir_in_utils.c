/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_in_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 17:08:03 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/19 17:11:39 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fork_redir_in_simple(t_execc *exe, t_command **prompt, char **envp)
{
	int	file;
	int	file2;

	if (fork() == 0)
	{
		file = open(exe->tmp->next->argv[0], O_RDONLY);
		dup2(file, STDIN_FILENO);
		if (exe->tmp->next->meta_char && \
		!ft_strncmp(exe->tmp->next->meta_char, ">", 1))
		{
			if (access(exe->tmp->next->next->argv[0], F_OK) == 0 \
			&& !ft_strncmp(exe->tmp->next->meta_char, ">>", 2))
				file2 = open(exe->tmp->next->next->argv[0], O_RDWR | O_APPEND);
			else if (access(exe->tmp->next->next->argv[0], F_OK) == 0 \
			&& !ft_strncmp(exe->tmp->next->next->meta_char, ">", 1))
				file2 = open(exe->tmp->next->next->argv[0], O_RDWR | O_TRUNC);
			else
				file2 = open(exe->tmp->next->next->argv[0], O_RDWR \
				| O_CREAT, 0777);
			dup2(file2, STDOUT_FILENO);
		}
		else if (exe->tmp->next->meta_char)
			dup2(exe->fd[exe->i][1], STDOUT_FILENO);
		ft_close_exit(&file, prompt, envp, exe);
	}
}

void	fork_redir_in_complex(t_execc *exe, t_command **prompt, \
char **envp, int	*file)
{
	int		file2;

	if (fork() == 0)
	{
		dup2(file[0], STDIN_FILENO);
		if (exe->tmp->next->meta_char && \
		!ft_strncmp(exe->tmp->next->meta_char, ">", 1))
		{
			if (access(exe->tmp->next->next->argv[0], F_OK) == 0 \
			&& !ft_strncmp(exe->tmp->next->meta_char, ">>", 2))
				file2 = open(exe->tmp->next->next->argv[0], O_RDWR | O_APPEND);
			else if (access(exe->tmp->next->next->argv[0], F_OK) == 0 \
			&& !ft_strncmp(exe->tmp->next->next->meta_char, ">", 1))
				file2 = open(exe->tmp->next->next->argv[0], O_RDWR | O_TRUNC);
			else
				file2 = open(exe->tmp->next->next->argv[0], O_RDWR \
				| O_CREAT, 0777);
			dup2(file2, STDOUT_FILENO);
			close (file2);
		}
		else if (exe->tmp->next->meta_char)
			dup2(exe->fd[exe->i][1], STDOUT_FILENO);
		ft_close_exit_complex(prompt, exe, file, envp);
	}
}

void	free_redir(char *a, char *res)
{
	free(a);
	free(res);
}

int	redir_prompt(t_execc *exe, int *file)
{
	char	*res;
	char	*a;
	char	*buffer;

	res = ft_calloc(100, sizeof(res));
	a = ft_strdup(exe->tmp->next->argv[0]);
	while (g_status != 130)
	{
		buffer = readline("> ");
		if (!buffer)
		{
			free_redir(a, res);
			return (-1);
		}
		if (!ft_strncmp(buffer, a, ft_strlen(a)))
		{
			free(buffer);
			break ;
		}
		write(file[1], buffer, ft_strlen(buffer));
		write(file[1], "\n", 1);
		free(buffer);
	}
	free_redir(a, res);
	return (0);
}
