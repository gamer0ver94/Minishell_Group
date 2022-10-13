/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 12:02:06 by memam             #+#    #+#             */
/*   Updated: 2022/10/13 15:14:34 by memam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

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

	i = 1;
	if (!args[i])
		return (ft_env(envp));
	while (args[i])
	{
		if (!is_valid_env_var(args[i]))
		{
			write(2, "export: not a valid identifier\n", 32);
			g_status = 1;
		}
		else if (args[i] != NULL)
		{
			set_env_var(envp, args[i]);
			g_status = 0;
		}
		i++;
	}
	return (0);
}
