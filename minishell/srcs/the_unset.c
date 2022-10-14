/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:55:44 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/14 12:09:16 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	the_unset(char **argv, char **envp)
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
