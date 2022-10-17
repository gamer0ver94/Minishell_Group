/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_in_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:12:46 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/17 18:08:14 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_close_exit(int *file, t_command **prompt, char **envp, t_execc *exe)
{
	close((*file));
	close_pipes(prompt, exe->fd);
	exec_simple(exe->tmp, envp);
	exit(0);
}

void	ft_close_exit_complex(t_command **prompt, t_execc *exe, int *file, \
char **envp)
{
	close_files(prompt, exe->files);
	close_pipes(prompt, exe->fd);
	close(file[0]);
	close(file[1]);
	exec_simple(exe->tmp, envp);
	exit(0);
}

void	export_list(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("declare -x %s\n", envp[i]);
		i++;
	}
}
