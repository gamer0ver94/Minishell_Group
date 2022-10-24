/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 23:44:25 by memam             #+#    #+#             */
/*   Updated: 2022/10/24 14:37:24 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_only_exit(t_command *command, char **envp)
{
	if (command->argv[1] == NULL)
	{
		ft_putstr_fd("exit\n", 1);
		free_prompt(&command);
		free_envp(envp);
		exit (g_status);
	}
	return (0);
}

int	ft_args_novalide(t_command *command, char **envp)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell : exit: ", 2);
	ft_putstr_fd(command->argv[1], 2);
	ft_putstr_fd(" numeric argument required\n", 2);
	free_prompt(&command);
	free_envp(envp);
	exit (255);
}

int	ft_is_exitcode(t_command *command)
{
	int	i;

	i = 0;
	while (command->argv[1][i] != '\0')
	{
		while (command->argv[1][i] == ' ')
			i++;
		if (command->argv[1][i] == '+' || command->argv[1][i] == '-')
			i++;
		while (command->argv[1][i] != '\0')
		{
			if (!ft_isdigit(command->argv[1][i]))
				return (0);
			i++;
		}						
	}
	return (1);
}

int	ft_exit(t_command *command, char **envp)
{
	int	i;

	i = 0;
	ft_only_exit(command, envp);
	if (!ft_is_exitcode(command))
		ft_args_novalide(command, envp);
	ft_putstr_fd("exit\n", 1);
	if (command->argv[1] && command->argv[2] == NULL)
	{
		i = ft_atoi(command->argv[1]);
		free_prompt(&command);
		free_envp(envp);
		exit((unsigned int)i);
	}
	if (command->argv[1] && command->argv[2] != NULL)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_status = 1;
		return (1);
	}
	return (0);
}
