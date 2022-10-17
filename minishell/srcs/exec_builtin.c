/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:04:54 by memam             #+#    #+#             */
/*   Updated: 2022/10/14 17:56:59 by memam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_env(t_command *prompt, char **envp)
{
	if (!ft_strncmp(prompt->cmd, "env", 3) && \
		!ft_strncmp(prompt->cmd, "env", ft_strlen(prompt->cmd)))
	{
		ft_env(envp);
		return (0);
	}
	if (!ft_strncmp(prompt->cmd, "export", 6) \
		&& !ft_strncmp(prompt->cmd, "export", ft_strlen(prompt->cmd)))
	{
		ft_export(prompt->argv, envp);
		return (0);
	}
	if (!ft_strncmp(prompt->cmd, "unset", 6)
		&& !ft_strncmp(prompt->cmd, "unset", ft_strlen(prompt->cmd)))
	{
		ft_unset(prompt->argv, envp);
		return (0);
	}
	return (1);
}

int	builtin(t_command *prompt, char **envp)
{
	if (!ft_strncmp(prompt->cmd, "echo", 4) && \
		!ft_strncmp(prompt->cmd, "echo", ft_strlen(prompt->cmd)))
	{
		ft_echo(prompt);
		return (0);
	}
	if (!ft_strncmp(prompt->cmd, "pwd", 3) && \
		!ft_strncmp(prompt->cmd, "pwd", ft_strlen(prompt->cmd)))
	{
		ft_pwd();
		return (0);
	}
	if (!ft_strncmp(prompt->cmd, "exit", 5) \
		&& !ft_strncmp(prompt->cmd, "exit", ft_strlen(prompt->cmd)))
	{
		ft_exit(prompt, envp);
		return (0);
	}
	return (1);
}
