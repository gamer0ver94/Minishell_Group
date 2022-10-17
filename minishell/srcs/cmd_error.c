/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:00:45 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/16 15:30:32 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_path(char **envp)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH", 4))
		{
			tmp = ft_strdup(envp[i]);
			tmp += 5;
			if (!ft_strncmp(tmp, getenv("PATH"), ft_strlen(tmp)))
			{
				tmp -= 5;
				free(tmp);
				return (0);
			}
			else
			{
				tmp -= 5;
				free(tmp);
			}
		}
		i++;
	}
	return (-1);
}
