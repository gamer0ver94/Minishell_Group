/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:15:50 by memam             #+#    #+#             */
/*   Updated: 2022/09/23 18:31:11 by memam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_unset(char **envp, char **args)
{
	int	i;
	int	index;

	i = 1;
	index = 0;
	if (!args[i])
		return (0);
	if (ft_strchr(args[1], '=') != NULL)
	{
		printf("unset: %s not a valid identifier\n", args[i]);
		return (1);
	}
	else
	{
		while (envp[index])
		{
			if (ft_strncmp(args[i], envp[index], ft_strlen(args[i])) == 0)
			{
				envp[index] = ft_strdup(envp[index + 1]);
				//free(envp[index + 1]);
				return (0);
			}
			else if (ft_strncmp(args[i], envp[index], ft_strlen(args[i])) == 0 && index--)
			{
				envp[index] = ft_strdup(envp[index - 1]);
				//free(envp[index + 1]);
				return (0);
			}
			index++;
		}
	}
	return (0);
}
