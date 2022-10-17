/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_gener.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:52:40 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/17 10:02:35 by memam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_env(char **new_envp, char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	while (new_envp[i])
	{
		new_envp[i] = NULL;
	}
}

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i] != NULL)
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	free_tmp(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i] != NULL)
	{
		free(envp[i]);
		i++;
	}
}

int	replace_var(char *parse, char *arg, char **envp)
{
	int	i;

	i = var_exist(parse, envp);
	free(envp[i]);
	envp[i] = ft_strdup(arg);
	return (0);
}

int	delete_var(char **envp, int j)
{
	free(envp[j]);
	while (envp[j])
	{
		envp[j] = envp[j + 1];
		j++;
	}
	return (0);
}
