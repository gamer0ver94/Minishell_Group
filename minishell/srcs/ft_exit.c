/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 23:44:25 by memam             #+#    #+#             */
/*   Updated: 2022/10/19 01:29:21 by memam            ###   ########.fr       */
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
		exit (0);
	}
	return (0);
}

// int	ft_many_args(t_command *command, char **envp)
// {
// 	if (command->argc > 2)
// 	{
// 		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
// 		//free_prompt(&command);
// 		//free_envp(envp);
// 		(void)envp;
// 		g_status = 1;
// 		return (1);
// 	}
	
// }

int	ft_args_noValide(t_command *command, char **envp)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell : exit: ", 2);
	ft_putstr_fd(command->argv[1], 2);
	ft_putstr_fd(" numeric argument required\n", 2);
	free_prompt(&command);
	free_envp(envp);
	exit (255);
}

int	ft_is_exitCode(t_command *command)
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
	ft_only_exit(command, envp);
	if (!ft_is_exitCode(command))
		ft_args_noValide(command, envp);
	if (command->argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 1);
		//free_prompt(&command);
		//free_envp(envp);
		g_status = 1;
	}
	i = ft_atoi(command->argv[1]);
	free_prompt(&command);
	free_envp(envp);
	ft_putstr_fd("exit\n", 1);
	exit((unsigned int)i);
}
