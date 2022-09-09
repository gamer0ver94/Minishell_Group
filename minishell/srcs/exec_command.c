/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:18:48 by dpaulino          #+#    #+#             */
/*   Updated: 2022/09/07 15:21:01 by dpaulino         ###   ########.fr       */
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

void    exec_command(t_command *prompt, char **envp)
{
	char	*path;
	char	**env_path;
	pid_t	pid;
	int		i;

	i = 0;
	env_path = ft_split(getenv("PATH"), ':');
	path = buildin_path(prompt->cmd);
	if (!ft_strncmp(prompt->cmd, "cd", 2))
	{
		cd_cmd(prompt, envp);
		return ;
	}
	if (!ft_strncmp(prompt->cmd, "exit", 4))
		execve(path, prompt->argv, envp);
	pid = fork();
	if (pid == 0)
	{
		if (execve(path, prompt->argv, envp) == -1)
		{
			free(path);
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
	}
	wait (&pid);
	free_args(env_path);
}