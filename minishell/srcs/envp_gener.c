/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_gener.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:52:40 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/12 16:59:16 by dpaulino         ###   ########.fr       */
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

// void	replace_envp(char **envp, int index)
// {
// 	char **tmp;
// 	int		i;

// 	tmp = malloc(sizeof(char *) * 1000);
// 	while (i < index)
// 	{
// 		tmp[i] = ft_strdup(envp[i]);
// 		i++;
// 	}
// }
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