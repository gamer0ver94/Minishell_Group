/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 12:02:06 by memam             #+#    #+#             */
/*   Updated: 2022/10/14 18:07:41 by memam            ###   ########.fr       */
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
		envp[j] = ft_strdup(arg);
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
		parse = parse_var(argv[i]);
		if (!parse)
			printf("bash: export: `%s`: not a valid identifier \n", argv[i]);
		else
			define_existence(argv[i], parse, envp);
		i++;
	}
	return (0);
}
