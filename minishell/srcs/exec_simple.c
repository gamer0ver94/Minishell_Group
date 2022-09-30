/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:18:48 by dpaulino          #+#    #+#             */
/*   Updated: 2022/09/30 20:39:22 by memam            ###   ########.fr       */
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
	if (!ft_strncmp(prompt->cmd, "echo", 4) && \
		!ft_strncmp(prompt->cmd, "echo", ft_strlen(prompt->cmd)))
	{
		ft_echo(prompt);
		return (0);
	}
	if (!ft_strncmp(prompt->cmd, "pwd", 3) && \
		!ft_strncmp(prompt->cmd, "echo", ft_strlen(prompt->cmd)))
	{
		ft_pwd();
		return (0);
	}
	if (!ft_strncmp(prompt->cmd, "env", 3) && \
		!ft_strncmp(prompt->cmd, "echo", ft_strlen(prompt->cmd)))
	{
		ft_env(envp);
		return (0);
	}
	if (!ft_strncmp(prompt->cmd, "export", 6) \
		&& !ft_strncmp(prompt->cmd, "export", ft_strlen(prompt->cmd)))
	{
		ft_export(envp, prompt->argv);
		return (0);
	}
	if (!ft_strncmp(prompt->cmd, "exit", 5) \
		&& !ft_strncmp(prompt->cmd, "exit", ft_strlen(prompt->cmd)))
	{
		ft_exit(prompt);
		return (0);
	}
	if (!ft_strncmp(prompt->cmd, "unset", 6)
		&& !ft_strncmp(prompt->cmd, "unset", ft_strlen(prompt->cmd)))
	{
		ft_unset(envp, prompt->argv);
		return (0);
	}
	// pour tester int ft_wildcards(char *args)
	if (!ft_strncmp(prompt->cmd, "mah", 4)
		&& !ft_strncmp(prompt->cmd, "mah", ft_strlen(prompt->cmd)))
	{
		ft_wildcards(prompt->argv[1]);
		return (0);
	}
	return (1);
}

int	exec_simple(t_command *prompt, char **envp)
{
	char	*path;
	char	**env_path;
	int		i;

	i = 0;
	env_path = ft_split(getenv("PATH"), ':');
	//path = buildin_path(prompt->cmd);
	if (!ft_strncmp(prompt->cmd, "cd", 2))
	{
		cd_cmd(prompt, envp);
		free_args(env_path);
		free(prompt->argv[0]);
		return (1);
	}
	

	//here is the exec_builtin
	if (exec_builtin(prompt, envp) == 0)
	{
		free(prompt->argv[0]);
		free_args(env_path); 
		return (1);
	}
	if (fork() == 0)
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
		exit(0);
	}
	waitpid(-1, NULL, 0);
	free_args(env_path);
	free(prompt->argv[0]);
	return (0);
}
