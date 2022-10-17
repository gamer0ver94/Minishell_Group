/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:15:50 by memam             #+#    #+#             */
/*   Updated: 2022/10/15 15:22:20 by memam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

int	ft_unset(char **argv, char **envp)
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	while (argv[i])
	{
		if (!is_valid_env_var(argv[i]) || argv[i][ft_strlen(argv[i])] == '=')
		{
			printf("bash: unset: `%s`: not a valid identifier \n", argv[i]);
			g_status = 1;
		}
		while (envp[j])
		{
			if (!ft_strncmp(argv[i], envp[j], ft_strlen(argv[i])) \
			&& envp[j][ft_strlen(argv[i])] == '=')
			{
				delete_var(envp, j);
				g_status = 0;
			}
			j++;
		}
		i++;
		j = 0;
	}
	return (g_status);
}
