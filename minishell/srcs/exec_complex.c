/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_complex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:48:05 by dpaulino          #+#    #+#             */
/*   Updated: 2022/09/21 21:09:30 by dpaulino         ###   ########.fr       */
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
	t_execc		exe;

	init_execc_struct(&exe, prompt);
	(void)envp;
	while (exe.tmp)
	{
		if (exe.tmp->id == 1)
			first_cmd(&exe, prompt, envp);
		else if (exe.tmp->meta_char && !ft_strncmp(exe.tmp->meta_char, "|", 1))
			pipef(&exe, prompt, envp);
		else if (exe.tmp->meta_char && !ft_strncmp(exe.tmp->meta_char, ">>", 2))
			redirect_out(&exe, prompt, envp);
		else if (exe.tmp->meta_char && !ft_strncmp(exe.tmp->meta_char, ">", 1))
			redirect_out(&exe, prompt, envp);
		else
			last_cmd(&exe, prompt, envp);
	}
	close_pipes(prompt, exe.fd);
	wait_childs(&exe);
	free_fd(prompt, exe.fd);
}



		
		// else if (exe.tmp->meta_char && !ft_strncmp(exe.tmp->meta_char, "<", 1))
		// else if (exe.tmp->meta_char && !ft_strncmp(exe.tmp->meta_char, "<<", 1))