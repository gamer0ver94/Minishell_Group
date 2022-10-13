/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:15:50 by memam             #+#    #+#             */
/*   Updated: 2022/10/13 17:09:54 by memam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

int	move_env(char **envp, int index)
{
	int		i;

	i = index;
	while (envp[i + 1])
	{
		envp[i] = ft_strdup(envp[i + 1]);
		envp[i +1] = NULL;
		i++;
	}
	envp = realloced_new_env(envp, i);
	return (0);
}

int	ft_unset(char **envp, char **args)
{
	int	index;
	int	i;

	i = 1;
	index = 0;
	if (!args[i])
		return (0);
	while (args[i])
	{
		if (!is_valid_env_var(args[i]))
		{
			write(2, "unset: not a valid identifier\n", 31);
			g_status = 1;
		}
		else
		{
			index = get_env_var_index(envp, args[i]);
			if (index != -1 && \
				ft_strncmp(args[i], envp[index], ft_strlen(args[i])) == 0)
				move_env(envp, index);
				g_status = 0;
		}
		i++;
	}
	return (0);
}
