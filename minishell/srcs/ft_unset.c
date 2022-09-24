/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:15:50 by memam             #+#    #+#             */
/*   Updated: 2022/09/24 18:22:07 by memam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	move_env(char **envp, int index)
{
	int	i;
	int	count;

	i = index;
	count = index;
	while (envp[i + 1])
	{
		envp[i] = ft_strdup(envp[i +1]);
		envp[i + 1] = NULL;
		i++;
		count++;
	}
	envp = realloced_new_env(envp, i);
	return (0);
}

int	ft_unset(char **envp, char **args)
{
	int	index;

	index = get_env_var_index(envp, args[1]);
	if (!args[1])
		return (0);
	if (ft_strchr(args[1], '=') != NULL)
	{
		printf("unset: %s not a valid identifier\n", args[1]);
		return (1);
	}
	else
		if (index != -1)
			move_env(envp, index);
	return (0);
}
