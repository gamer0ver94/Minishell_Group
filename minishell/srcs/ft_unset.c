/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:15:50 by memam             #+#    #+#             */
/*   Updated: 2022/10/17 17:10:15 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_unset(char **argv, char **envp)
{
	int	i;
	int	j;

	j = -1;
	i = 1;
	while (argv[i])
	{
		if (!is_valid_env_var(argv[i]) || argv[i][ft_strlen(argv[i])] == '=')
		{
			printf("bash: unset: `%s`: not a valid identifier \n", argv[i]);
			g_status = 1;
		}
		while (envp[++j])
		{
			if (!ft_strncmp(argv[i], envp[j], ft_strlen(argv[i])) \
			&& envp[j][ft_strlen(argv[i])] == '=')
			{
				delete_var(envp, j);
				g_status = 0;
			}
		}
		i++;
		j = 0;
	}
	return (g_status);
}
