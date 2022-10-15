/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 11:03:50 by memam             #+#    #+#             */
/*   Updated: 2022/10/15 23:41:31 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

void	ft_echo_op(t_command *command)
{
	int	i;

	i = 2;
	while (command->argv[i])
	{
		if (ft_strncmp(command->argv[i], "-n", 2) != 0)
		{
			while (command->argv[i])
			{
				printf("%s", command->argv[i]);
				if (command->argv[++i])
					printf(" ");
			}
		}		
		i++;
	}
}

int	ft_echo(t_command *command)
{
	int		i;

	g_status = 0;
	if (command->argv[1] == NULL)
		printf("\n");
	else if (ft_strncmp(command->argv[1], "-n", 2) == 0)
		ft_echo_op(command);
	else
	{
		i = 1;
		while (command->argv[i])
		{
			printf("%s", command->argv[i]);
			if (command->argv[i])
				printf(" ");
			i++;
		}
		printf("\n");
	}
	return (0);
}
