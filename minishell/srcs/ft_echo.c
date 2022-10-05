/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 11:03:50 by memam             #+#    #+#             */
/*   Updated: 2022/10/05 18:25:38 by memam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

	if (command->argv[1] == NULL)
	{
		printf("\n");
		return (0);
	}	
	else if (ft_strncmp(command->argv[1], "-n", 2) == 0)
	{
		ft_echo_op(command);
		return (0);
	}
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
