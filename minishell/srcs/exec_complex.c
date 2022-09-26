/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_complex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:48:05 by dpaulino          #+#    #+#             */
/*   Updated: 2022/09/26 13:37:55 by memam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	wait_childs(t_execc *exe)
{
	while (exe->j-- > 0)
	{
		waitpid(-1, NULL, 0);
	}
}

void	exec_complex(t_command **prompt, char **envp)
{
	t_execc		*exe;

	exe = malloc(sizeof(t_execc));
	init_execc_struct(exe, prompt);
	(void)envp;
	while (exe->tmp)
	{
		write(2, "as\n", 3);
		if (exe->tmp->id == 1)
			first_cmd(exe, prompt, envp);
		else if (exe->tmp->meta_char && !ft_strncmp(exe->tmp->meta_char, "|", 1))
			pipef(exe, prompt, envp);
		else if (exe->tmp->meta_char && !ft_strncmp(exe->tmp->meta_char, ">>", 2))
			redirect_out(exe, prompt, envp);
		else if (exe->tmp->meta_char && !ft_strncmp(exe->tmp->meta_char, ">", 1))
			redirect_out(exe, prompt, envp);
		// else if (exe->tmp->meta_char && !ft_strncmp(exe->tmp->meta_char, "<", 1))
		// 	redirect_in(exe, prompt, envp);
		// else if (exe->tmp->meta_char && !ft_strncmp(exe->tmp->meta_char, "<<", 2))
		// 	redirect_in(&exe, prompt, envp);	
		else
			last_cmd(exe, prompt, envp);
	}
	close_pipes(prompt, exe->fd);
	wait_childs(exe);
	free_fd(exe, prompt);
}



		
		// else if (exe.tmp->meta_char && !ft_strncmp(exe.tmp->meta_char, "<", 1))