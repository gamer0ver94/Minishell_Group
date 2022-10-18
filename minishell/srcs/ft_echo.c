/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 11:03:50 by memam             #+#    #+#             */
/*   Updated: 2022/10/18 22:47:12 by memam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

int	ft_echo_flag(char *args)
{
	int	i;
	int flag;

	i = 0;
	flag = 0;
	if (args[i] != '-')
		return(flag);
	i++;
	while (args[i] && args[i] == 'n')
		i++;
	if (args[i] == '\0')
		flag = 1;
	return (flag);	
}

void	ft_echo_print(t_command *command, int flag, int i)
{
	if (!command->argv[i])
	{
		if (!flag)
			ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	while (command->argv[i])
	{
		ft_putstr_fd(command->argv[i], STDOUT_FILENO);
		if (command->argv[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		else if (!command->argv[i + 1] && !flag)
			ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
	

}

int	ft_echo(t_command *command)
{
	int		i;
	int		flag;

	flag = 0;
	i = 1;
	while (command->argv[i] && ft_echo_flag(command->argv[i]))
	{
		flag = 1;
		i++;
	}
	ft_echo_print(command, flag, i);
	g_status = 0;
	return (0);
}
