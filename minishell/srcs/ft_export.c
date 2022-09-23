/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 12:02:06 by memam             #+#    #+#             */
/*   Updated: 2022/09/23 13:23:39 by memam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*  
*       check if the identifier is valid for evrionnment variable.
*       return true if the identifier contains only alphanumeric or '_'
*       or false if not.
*/

int	is_valid_env_var_idVar(char *var)
{
	int	i;

	i = 0;
	if (ft_isalpha(var[i]) == 0 && var[i] != '_')
		return (0);
	i++;
	while (var[i] && var[i] != '=')
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
/* 
*       add the given variable to the environment variable.
*       return 0 if all args added to env.
*       return 1 if one or more args not added to env. 
*/

int	ft_export(char **envp, char **args)
{
	int		i;
	int		e;
	//char	**tmp;

	i = 1;
	e = 0;
	if (!args[i])
		return (ft_env(envp));
	while (args[i])
	{
		if (!is_valid_env_var_idVar(args[i]))
		{
			printf("export: %s not a valid identifier\n", args[i]);
			return (1);
		}
		else if (args[i] != NULL)
		{	printf("form export\n");

			set_env_var(envp, args[i]);
		}
		i++;
	}
	free(args[0]);
	free(args[i]);
	return (0);
}
