/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:07:00 by dpaulino          #+#    #+#             */
/*   Updated: 2022/09/28 23:47:46 by dpaulino         ###   ########.fr       */
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
		while (envp[i++])
			if (!ft_strncmp(envp[i - 1], "PWD", 3))
				envp[i - 1] = ft_strjoin("PWD=", getcwd(new_pwd, 1000));
	}
	else if (!(*prompt).argv[1])
		chdir(getenv("HOME"));
	else
		perror("bash");
	return (0);
}
