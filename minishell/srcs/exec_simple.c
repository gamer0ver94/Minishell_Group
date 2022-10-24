/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:18:48 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/24 16:11:50 by dpaulino         ###   ########.fr       */
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
		else
		{
			if (WEXITSTATUS(status) == 127)
				g_status = 127;
			else if (WEXITSTATUS(status) == 126)
				g_status = 126;
			else
				g_status = 1;
		}
	}
}

int	exec_simple(t_command *prompt, char **envp)
{
	char	**env_path;
	int		i;
	pid_t	pid;

	if (is_cmd_exception(prompt))
	{
		signal(SIGINT, &sighandler2);
		signal(SIGQUIT, &sighandler2);
	}
	i = 0;
	env_path = ft_split(getenv("PATH"), ':');
	if (verify_cd_exit(prompt, envp, env_path))
		return (1);
	if (builtin_env(prompt, envp) == 0 || builtin(prompt, envp) == 0)
	{
		free_args(env_path);
		return (1);
	}
	pid = exec_fork(prompt, envp, env_path, &i);
	wait_fork(&pid);
	free_args(env_path);
	return (0);
}
