/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:34:01 by memam             #+#    #+#             */
/*   Updated: 2022/09/19 00:13:38 by memam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env(t_command *command)
{
	int		i;

	i = 0;
	if (!command->envp)
		return (EXIT_FAILURE);
	while (command->envp[i])
	{
		printf("%s\n", command->envp[i]);
		i++;
	}
	printf("😀😀😀😀😀😀😀\n");
	return (0);
}
