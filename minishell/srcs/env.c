/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 22:22:35 by memam             #+#    #+#             */
/*   Updated: 2022/09/23 13:08:12 by memam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* 
*       count hom many original environemet variable there are.
*       return the unmber of environemet variable.
*/
int	env_var_count(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

void	free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

int	get_env_var_index(char **env, char *var)
{
	int		i;
	char	**tmp;

	tmp = ft_split(var, '=');
	if (!tmp)
		return (-1);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(tmp[0], env[i], ft_strlen(tmp[0])) == 0)
		{
			free_tab(tmp);
			return (i);
		}
		i++;
	}
	free_tab(tmp);
	return (-1);
}

/* 
*       add an environment variable wthit the given identifier
*       corresponding to the given value.
*       if the identifier already exists in the environment, the
*       value will be update.
*       if not, it will creates a new entry.
*       return true if the operation was sucessful or false in case of error.
*/

int	set_env_var(char **envp, char *args)
{
	int		index;

	index = get_env_var_index(envp, args);
	if (index != -1 && envp[index])
	{
		envp[index] = ft_strdup(args);
	}
	else
	{
		index = env_var_count(envp);
		envp[index] += 1;
		envp[index] = ft_strdup(args);
	}
	return (0);
}
