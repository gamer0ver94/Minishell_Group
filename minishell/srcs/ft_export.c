/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 12:02:06 by memam             #+#    #+#             */
/*   Updated: 2022/10/15 15:10:17 by memam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

int	var_exist(char *arg, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(arg, envp[i], ft_strlen(arg)))
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

char	*parse_var(char *var)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_calloc(100, sizeof(char));
	while (var[i] && var[i] != '=')
	{
		if (var[i] == ' ')
		{
			free(tmp);
			return (NULL);
		}
		tmp[i] = var[i];
		i++;
	}
	if (!var[i] || var[i] != '=')
	{
		free(tmp);
		return (NULL);
	}
	return (tmp);
}

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

void	define_existence(char *arg, char *parse, char **envp)
{
	int	j;

	j = 0;
	if (var_exist(parse, envp) >= 0)
	{
		replace_var(parse, arg, envp);
		g_status = 0;
	}
	else
	{
		while (envp[j])
		{
			j++;
		}
		free(envp[j]);
		envp[j] = envp[j - 1];
		envp[j - 1] = ft_strdup(arg);
	}
	free(parse);
}

int	ft_export(char **argv, char **envp)
{
	int		i;
	char	*parse;

	parse = NULL;
	i = 1;
	while (argv[i])
	{
		if (!is_valid_env_var(argv[i]))
		{
			printf("bash: export: `%s`: not a valid identifier \n", argv[i]);
			g_status = 1;
		}
		else if (ft_strchr(argv[i], '=') && argv[i] != NULL)
		{
			parse = parse_var(argv[i]);
			define_existence(argv[i], parse, envp);
			g_status = 0;
		}
		i++;
	}
	return (g_status);
}
