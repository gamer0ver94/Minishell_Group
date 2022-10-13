/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:07:00 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/13 13:09:35 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cd_cmd(t_command *prompt, char **envp)
{
	int		i;
	int		index;
	char	new_pwd[1000];
	char	old_pwd[1000];

	i = 0;
	index = get_env_var_index(envp, "OLDPWD");
	if (index != -1)
		envp[index] = ft_strjoin("OLDPWD=", getcwd(old_pwd, sizeof(old_pwd)));
	if (prompt->argv[1] && !chdir(prompt->argv[1]))
	{
		while (envp[i++])
		{
			if (!ft_strncmp(envp[i - 1], "PWD", 3))
			{
				free(envp[i - 1]);
				envp[i - 1] = ft_strjoin("PWD=", getcwd(new_pwd, 1000));
			}
		}
	}
	else if (!(*prompt).argv[1])
		chdir(getenv("HOME"));
	else
		perror("bash");
	return (0);
}
