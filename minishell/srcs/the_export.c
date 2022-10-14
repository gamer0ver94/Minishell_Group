/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 08:55:37 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/14 10:54:12 by dpaulino         ###   ########.fr       */
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
	return (0);
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
	if (!var[i] || var[i] != '=' || !var[i + 1])
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
	if (var_exist(parse, envp))
	{
		replace_var(arg, envp);
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

int	the_export(char **argv, char **envp)
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
