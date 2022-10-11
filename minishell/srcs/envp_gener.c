/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_gener.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:52:40 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/11 13:01:38 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void create_env(char **new_envp, char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
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

// int	add_env(char **envp, char *env)
// {
// 	return (1);
// }

// int	delete_env(char **envp, char *env)
// {
// 	int	i;

// 	i = 0;
// 	while ()
// 	return (1);
// }