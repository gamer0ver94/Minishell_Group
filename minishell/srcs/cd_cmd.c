/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:07:00 by dpaulino          #+#    #+#             */
/*   Updated: 2022/09/26 13:35:41 by memam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cd_cmd(t_command *prompt, char **envp)
{
	int		i;
	char	new_pwd[1000];

	i = 0;
	if (!chdir((*prompt).argv[1]))
	{
		while (envp[i])
		{
			if (!ft_strncmp(envp[i], "PWD", 3))
			{
				envp[i] = ft_strjoin("PWD=", getcwd(new_pwd, 1000));
			}
			i++;
		}
	}
	else if (!(*prompt).argv[1])
	{
		chdir(getenv("HOME"));
	}
	else
		perror("bash");
	return (0);
}
//PS need to update oldpwd and pwd