/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 11:03:50 by memam             #+#    #+#             */
/*   Updated: 2022/10/17 16:33:13 by dpaulino         ###   ########.fr       */
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
		printf("\n");
	else if (ft_strncmp(command->argv[1], "-n", 2) == 0)
	{
		ft_echo_op(command);
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
	g_status = 0;
	return (0);
}
