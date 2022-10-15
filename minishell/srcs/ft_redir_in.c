/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 12:31:33 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/15 23:42:54 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redirect_in(t_execc *exe, t_command **prompt, char **envp)
{
	if (access(exe->tmp->next->argv[0], F_OK) != 0)
	{
		write(2, "bash : ", 7);
		write (2, exe->tmp->next->argv[0], ft_strlen(exe->tmp->next->argv[0]));
		write (2, " No such file or directory\n", 27);
		exe->tmp = exe->tmp->next;
	}
	else
	{
		fork_redir_in_simple(exe, prompt, envp);
		exe->i++;
		exe->tmp = exe->tmp->next;
		if (exe->tmp->meta_char)
			exe->tmp = exe->tmp->next;
	}
}

void	redirect_in_complex(t_execc *exe, t_command **prompt, char **envp)
{
	int		*file;

	file = malloc(sizeof(int) * 2);
	pipe(file);
	if (redir_prompt(exe, file) == -1)
	{
		while (exe->tmp->next)
				exe->tmp = exe->tmp->next;
		free(file);
		return ;
	}
	fork_redir_in_complex(exe, prompt, envp, file);
	close(file[0]);
	close(file[1]);
	free(file);
	exe->i++;
	exe->tmp = exe->tmp->next;
	if (exe->tmp->meta_char)
		exe->tmp = exe->tmp->next;
}
