/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 11:03:50 by memam             #+#    #+#             */
/*   Updated: 2022/10/18 16:17:29 by memam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

void	ft_echo_op_help(char **args)
{
	int	i;

	i = 0;
	if (ft_strncmp(args[i], "-n", 2) != 0)
	{
		while (args[i])
		{
			printf("%s", args[i]);
			if (args[++i])
				printf(" ");
		}
	}	
}

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
		else
			ft_echo_op_help(&command->argv[i]);
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
