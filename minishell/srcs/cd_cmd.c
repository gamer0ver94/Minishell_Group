/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:07:00 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/11 12:06:20 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cd_cmd(t_command *prompt, char **envp)
{
	int		i;
	int		index;
	char	new_pwd[1000];
	char	OLDPWD[1000];
	static	char *old_pwd;
	static	char	*pwd;
	i = 0;
	index = get_env_var_index(envp, "OLDPWD");
	if (index != -1)
	{
		if (old_pwd)
		{
			free(old_pwd);
			printf("freed\n");
		}
		old_pwd = ft_strjoin("OLDPWD=", getcwd(OLDPWD, sizeof(OLDPWD)));
		envp[index] = old_pwd;
	}
	if (!chdir((*prompt).argv[1]))
	{
		while (envp[i++])
			if (!ft_strncmp(envp[i - 1], "PWD", 3))
			{
				if (pwd)
					free(pwd);
				pwd = ft_strjoin("PWD=", getcwd(new_pwd, 1000));
				envp[i - 1] = pwd;
			}
	}
	else if (!(*prompt).argv[1])
		chdir(getenv("HOME"));
	else
		perror("bash");
	return (0);
}
