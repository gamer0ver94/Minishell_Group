/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:15:50 by memam             #+#    #+#             */
/*   Updated: 2022/10/13 21:46:10 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	move_env(char **envp, int index)
{
	int		i;
	int		count;
	char	*tmp;

	tmp = ft_calloc(1, sizeof(char));
	i = index;
	count = index;
	while (envp[i + 1])
	{
		free(envp[i]);
		free(tmp);
		tmp = ft_strdup(envp[i + 1]);
		envp[i] = ft_strdup(tmp);
		i++;
		count++;
	}
	free(envp[i]);
	envp[i] = ft_strdup("lalalla");
	free(tmp);
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
		if (ft_strchr(args[1], '=') != NULL)
		{
			printf("unset: %s not a valid identifier\n", args[1]);
			return (1);
		}
		else
		{
			index = get_env_var_index(envp, args[i]);
			if (index != -1 && \
				ft_strncmp(args[i], envp[index], ft_strlen(args[i])) == 0)
				move_env(envp, index);
		}
		i++;
	}
	return (0);
}
