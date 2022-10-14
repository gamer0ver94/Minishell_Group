/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:15:50 by memam             #+#    #+#             */
/*   Updated: 2022/10/14 17:58:54 by memam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_unset(char **argv, char **envp)
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	while (argv[i])
	{
		while (envp[j])
		{
			if (!ft_strncmp(argv[i], envp[j], ft_strlen(argv[i])) \
			&& envp[j][ft_strlen(argv[i])] == '=')
			{
				delete_var(envp, j);
			}
			j++;
		}
		i++;
		j = 0;
	}
	return (0);
}
