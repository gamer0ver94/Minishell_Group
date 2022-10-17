/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 11:03:50 by memam             #+#    #+#             */
/*   Updated: 2022/10/17 09:53:08 by memam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

void	ft_echo_op(t_command *command)
{
	int		i;
	char	*tem;

	i = 1;
	while (command->argv[i])
	{
		if (command->argv[i][0] == '-')
		{
			tem = ft_strtrim(command->argv[i], "n");
			if (ft_strncmp(tem, "-", ft_strlen(tem)) != 0)
			{
				while (command->argv[i])
				{
					printf("%s", command->argv[i]);
					if (command->argv[i + 1])
						printf(" ");
					i++;
				}
			}
			free(tem);
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
		g_status = 0;
	}	
	else if (ft_strncmp(command->argv[1], "-n", 2) == 0)
	{
		ft_echo_op(command);
		g_status = 0;
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
	return (g_status);
}
