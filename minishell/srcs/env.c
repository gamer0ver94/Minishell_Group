/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 22:22:35 by memam             #+#    #+#             */
/*   Updated: 2022/09/20 19:41:11 by memam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* @ env_var_count
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
/* @ get_env_var_index
*       searche for the given variable in the environment variables.
*       
*       return the index of the variable in the environment 
*       matching the given string.
*       the given string must be a full variable name.
*       return -1 if the string cannot be found in the environment.
*/

/* @ realloc_env_var
*   
*
*
*/
char	**realloc_env_var(char **envp, int index)
{
	char	**new_var;
	int		i;

	new_var = ft_calloc(index + 1, sizeof * new_var);
	if (!new_var)
		return (NULL);
	i = 0;
	while (envp[i] && i < index)
	{
		new_var[i] = ft_strdup(envp[i]);
		//free(envp[i]);
		i++;
	}
	return (new_var);
}

int	get_env_var_index(char **env, char *var)
{
	int		i;
	char	*tmp;

	tmp = ft_strjoin(var, "=");
	if (!tmp)
		return (-1);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(tmp, env[i], ft_strlen(tmp)) == 0)
		{
			free(tmp);
			return (i);
		}
		i++;
	}
	free(tmp);
	return (-1);
}

/* @ srt_env_var
*       add an environment variable wthit the given identifier
*       corresponding to the given value.
*       if the identifier already exists in the environment, the
*       value will be update.
*       if not, it will creates a new entry.
*       return true if the operation was sucessful or false in case of error.
*/

bool	set_env_var(char **envp, char *idVar, char *value)
{
	int		index;
	char	*tmp;

	index = get_env_var_index(envp, idVar);
	if (value == NULL)
		value = "";
	tmp = ft_strjoin("=", value);
	if (!tmp)
		return (NULL);
	if (index != -1 && envp[index])
	{
		printf("identifier %s\n", idVar);
		printf(" the new value  %s\n", tmp);
		envp[index] = ft_strjoin(idVar, tmp);
		printf("environment variable with the new value %s\n", envp[index]);
	}
	else
	{
		index = env_var_count(envp);
		printf("index avone %d\n", index);
		envp = realloc_env_var(envp, index + 1);
		printf("identifier %s\n", idVar);
		printf(" the new value  %s\n", tmp);
		if (!envp)
			return (NULL);
		envp[index] = ft_strjoin(idVar, tmp);
		printf("env variable with the new var %d %s\n", index, envp[index]);
	}
	free(tmp);
	return (0);
}
