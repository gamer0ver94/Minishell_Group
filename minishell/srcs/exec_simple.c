/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:18:48 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/07 10:25:39 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int g_status;

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

int	exec_simple(t_command *prompt, char **envp)
{
	char	*path;
	char	**env_path;
	int		i;
	int		status;
	pid_t	pid;

	i = 0;
	env_path = ft_split(getenv("PATH"), ':');
	if (!ft_strncmp(prompt->cmd, "cd", 2))
	{
		cd_cmd(prompt, envp);
		free_args(env_path);
		free(prompt->argv[0]);
		return (1);
	}
	//here is the exec_builtin
	if (builtin_env(prompt, envp) == 0 ||builtin(prompt) == 0)
	{
		free_args(env_path); 
		return (1);
	}
	pid = fork();
	if (pid == 0)
	{
		if (access(prompt->argv[0], F_OK) == 0)
			execve(prompt->argv[0], prompt->argv, envp);
		else
		{
			while (env_path[i])
			{
				path = get_single_path(prompt->cmd, env_path[i]);
				if (execve(path, prompt->argv, envp) == -1)
				{
					free(path);
					i++;
				}
			}
			write(2, prompt->cmd, ft_strlen(prompt->cmd));
			write(2, ": command not found\n", 20);
			exit(127);
		}
	}
	if (waitpid(pid, &status, 0))
	{
		if (WIFEXITED(status) && !WEXITSTATUS(status))
		{
			g_status = 0;
		}
		else if (WIFEXITED(status) && WEXITSTATUS(status))
		{
			if (WEXITSTATUS(status) == 127)
				g_status = 127;
			else
				g_status = 2;
		}
		else
			g_status = 1;
	}
	free_args(env_path);
	free(prompt->argv[0]);
	return (0);
}
