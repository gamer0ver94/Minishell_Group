/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 12:02:06 by memam             #+#    #+#             */
/*   Updated: 2022/10/11 09:29:06 by memam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_valid_env_var(char *var)
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

int	ft_export(char **envp, char **args)
{
	int		i;
	int		ret;

	i = 1;
	ret = 0;
	if (!args[i])
		return (ft_env(envp));
	while (args[i])
	{
		if (!is_valid_env_var(args[i]))
		{
			printf("export: %s not a valid identifier\n", args[i]);
			ret = 1;
		}
		else if (ft_strchr(args[i], '=') != NULL)
		{
			set_env_var(envp, args[i]);
		}
		i++;
	}
	return (ret);
}
