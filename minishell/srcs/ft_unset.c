/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:15:50 by memam             #+#    #+#             */
/*   Updated: 2022/09/23 00:08:35 by memam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_unset(char **envp, char **args)
{
	int	i;
	int	index;

	i = 1;
	index = 0;
	if (!is_valid_env_var_idVar(args[i]) || ft_strchr(args[i], '='))
	{
		printf("unset: %s not a valid identifier\n", args[i]);
		return (1);
	}
	else
	{
		index = get_env_var_index(envp, args[i]);
		if (index == -1)
			printf("unset: %s: variable not found\n", args[i]);
		
		printf("is ok %s\n", envp[index]);
		while (envp[index])
		{
			envp[index] = ft_strdup(envp[index + 1]);
			free(envp[index + 1]);
		}
	}
	return (0);
}
