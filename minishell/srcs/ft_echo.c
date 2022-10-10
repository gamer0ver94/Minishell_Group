/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 11:03:50 by memam             #+#    #+#             */
/*   Updated: 2022/09/26 14:13:55 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_echo(t_command *command)
{
	int		i;

	i = 2;
	if (command->argv[1] == NULL)
	{
		printf("\n");
		return (0);
	}	
	else if (ft_strncmp(command->argv[1], "-n", 2) == 0)
	{
		while (command->argv[i])
		{
			if (ft_strncmp(command->argv[i], "-n", 2) != 0)
				printf("%s", command->argv[i]);
			i++;
		}
		return (0);
	}
	else
	{
		i = 1;
		while (command->argv[i])
		{
			printf("%s ", command->argv[i]);
			i++;
		}
		printf("\n");
	}
	return (0);
}
//this function needs to handle -n
