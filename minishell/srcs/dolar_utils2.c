/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:07:33 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/24 16:13:17 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*dolar_utils2(char *tmp2, char *aux, int *lock, t_command **prompt)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*prompt)->envp[i])
	{
		if (!ft_strncmp(tmp2, (*prompt)->envp[i], \
			ft_strlen((*prompt)->envp[i])) \
			&& !ft_strncmp(tmp2, (*prompt)->envp[i], ft_strlen(tmp2)))
		{
			ft_bzero(tmp2, ft_strlen(tmp2));
			tmp = ft_strdup((*prompt)->envp_val[i]);
			tmp[ft_strlen(tmp)] = '\0';
			if ((*lock))
			{
				tmp = ft_strjoin(tmp, aux);
			}
			return (tmp);
		}
		i++;
	}
	return (NULL);
}

int	is_cmd_exception(t_command *prompt)
{
	if (ft_strncmp(prompt->cmd, "grep", ft_strlen(prompt->cmd)) \
	&& prompt->argv[1])
		return (0);
	else if (!ft_strncmp(prompt->cmd, "cat", ft_strlen(prompt->cmd)))
		return (1);
	else if (!ft_strncmp(prompt->cmd, "wc", ft_strlen(prompt->cmd)))
		return (1);
	else if (!ft_strncmp(prompt->cmd, "grep", ft_strlen(prompt->cmd)) \
	&& prompt->argv[1])
		return (1);
	else if (!ft_strncmp(prompt->cmd, "as", ft_strlen(prompt->cmd)))
		return (1);
	else
		return (0);
	return (0);
}

int	verify_cd_exit(t_command *prompt, char **envp, char **env_path)
{
	if (!ft_strncmp(prompt->cmd, "cd", 2))
	{
		cd_cmd(prompt, envp);
		free_args(env_path);
		return (1);
	}
	if (!ft_strncmp(prompt->cmd, "exit", 5))
		free_args(env_path);
	return (0);
}
