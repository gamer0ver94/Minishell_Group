/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:18:48 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/21 13:44:29 by memam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*buildin_path(char *cmd)
{
	char	*str;
	char	*tmp;

	tmp = ft_strdup("builtin/");
	str = ft_strjoin(tmp, cmd);
	free(tmp);
	return (str);
}

char	*get_single_path(char *cmd, char *env_path)
{
	char	*str;
	char	*tmp;

	tmp = ft_strdup(env_path);
	str = ft_strjoin(tmp, "/");
	free(tmp);
	tmp = ft_strjoin(str, cmd);
	free(str);
	return (tmp);
}

pid_t	exec_fork(t_command *prompt, char **envp, char **env_path, int *i)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid == 0)
	{
		execve(prompt->cmd, prompt->argv, envp);
		while (env_path[(*i)])
		{
			if (check_path(envp) == -1)
				break ;
			path = get_single_path(prompt->cmd, env_path[(*i)]);
			if (execve(path, prompt->argv, envp) == -1)
			{
				free(path);
				(*i)++;
			}
		}
		verify_access(prompt);
	}
	return (pid);
}

void	wait_fork(pid_t *pid)
{
	int		status;

	if (waitpid((*pid), &status, 0))
	{
		if (WIFEXITED(status) && !WEXITSTATUS(status))
		{
			g_status = 0;
		}
		else if (WIFEXITED(status) && WEXITSTATUS(status))
		{
			if (WEXITSTATUS(status) == 127)
				g_status = 127;
			else if (WEXITSTATUS(status) == 126)
				g_status = 126;
			else
				g_status = 1;
		}
		else
			g_status = 2;
	}
}

int	exec_simple(t_command *prompt, char **envp)
{
	char	**env_path;
	int		i;
	pid_t	pid;

	i = 0;
	env_path = ft_split(getenv("PATH"), ':');
	if (!ft_strncmp(prompt->cmd, "cd", 2))
	{
		cd_cmd(prompt, envp);
		free_args(env_path);
		return (1);
	}
	if (!ft_strncmp(prompt->cmd, "exit", 5))
		free_args(env_path);
	if (builtin_env(prompt, envp) == 0 || builtin(prompt, envp) == 0)
	{
		//free_args(env_path); valgrind leake exit
		return (1);
	}
	get_signals(2);
	pid = exec_fork(prompt, envp, env_path, &i);
	wait_fork(&pid);
	free_args(env_path);
	return (0);
}
