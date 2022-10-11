/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 22:22:35 by memam             #+#    #+#             */
/*   Updated: 2022/10/11 19:12:18 by memam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	int	i;

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
			tmp = NULL;
			return (i);
		}
		i++;
	}
	free_tab(tmp);
	tmp = NULL;
	return (-1);
}

char	**realloced_new_env(char **env, int index)
{
	char	**tmp;
	int		i;

	tmp = (char **)ft_calloc(index + 1, sizeof * tmp);
	if (!tmp)
		return (NULL);
	i = 0;
	while (env[i] && i < index)
	{
		tmp[i] = ft_strdup(env[i]);
		i++;
	}
	while (tmp[i])
	{
		env[i] = tmp[i];
		i++;
	}
	free_args(tmp);
	return (env);
}

int	set_env_var(char **envp, char *args)
{
	int		index;
	char	*tmp;

	index = get_env_var_index(envp, args);
	if (index != -1 && envp[index])
	{
		tmp = ft_strdup(args);
		envp[index] = tmp;
	}
	else
	{
		index = env_var_count(envp);
		realloced_new_env(envp, index + 1);
		envp[index] = envp[index -1];
		tmp = strcpy(args);
		envp[index - 1] = tmp;
		envp[index + 1] = NULL;
	}
	//free(tmp);
	return (0);
}
