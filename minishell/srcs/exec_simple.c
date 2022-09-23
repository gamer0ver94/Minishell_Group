/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:18:48 by dpaulino          #+#    #+#             */
/*   Updated: 2022/09/23 12:44:17 by memam            ###   ########.fr       */
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
// here is the exec (echo),(pwd),(env), 
int    exec_builtin(t_command *prompt, char **envp)
{
	if (!ft_strncmp(prompt->cmd, "echo", ft_strlen(prompt->cmd)))
	{
		ft_echo(prompt);
		return (0);
	}
	if (!ft_strncmp(prompt->cmd, "pwd", ft_strlen(prompt->cmd)))
	{
		ft_pwd();
		return (0);
	}
	if (!ft_strncmp(prompt->cmd, "env", ft_strlen(prompt->cmd)))
	{
		ft_env(envp);
		return (0);
	}
	if (!ft_strncmp(prompt->cmd, "export", ft_strlen(prompt->cmd)))
	{
		ft_export(envp, prompt->argv);
		return (0);
	}
	if (!ft_strncmp(prompt->cmd, "exit", ft_strlen(prompt->cmd)))
	{
		ft_exit(prompt->argv);
		return (0);
	}
	if (!ft_strncmp(prompt->cmd, "unset", ft_strlen(prompt->cmd)))
	{
		ft_unset(envp, prompt->argv);
		return (0);
	}
	return (1);
}

void	exec_simple(t_command *prompt, char **envp)
{
	char	*path;
	char	**env_path;
	int		pid;
	int		i;

	i = 0;
	env_path = ft_split(getenv("PATH"), ':');
	path = buildin_path(prompt->cmd);
	if (!ft_strncmp(prompt->cmd, "cd", 2))
	{
		cd_cmd(prompt, envp);
		return ;
	}
	//here is the exec_builtin
	if (exec_builtin(prompt, envp) == 0)
		return ;
	pid = fork();
	if (pid == 0)
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
		printf("%s: command not found\n", prompt->cmd);
	}
	waitpid(pid, NULL, 0);
	free_args(env_path);
}
