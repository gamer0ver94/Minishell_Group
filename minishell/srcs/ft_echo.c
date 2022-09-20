/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 11:03:50 by memam             #+#    #+#             */
/*   Updated: 2022/09/20 12:37:34 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_echo(t_command *command)
{
	int		i;

	i = 1;
	if (ft_strncmp(command->argv[0], "-n", 2) == 0)
	{
		printf("\n");
		return (0);
	}
	while (command->argv[i])
	{
		printf("%s ", command->argv[i]);
		i++;
	}
	printf("😀");
	printf("\n");
	return (0);
}
//this function needs to handle -n
