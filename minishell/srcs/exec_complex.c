/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_complex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:48:05 by dpaulino          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/09/22 15:12:31 by dpaulino         ###   ########.fr       */
=======
/*   Updated: 2022/09/26 12:10:25 by dpaulino         ###   ########.fr       */
>>>>>>> main
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
<<<<<<< HEAD
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
		// else if (exe.tmp->meta_char && !ft_strncmp(exe.tmp->meta_char, "<", 1))
		// 	redirect_in(&exe, prompt, envp);
		else
			last_cmd(&exe, prompt, envp);
	}
	close_pipes(prompt, exe.fd);
	wait_childs(&exe);
	free_fd(prompt, exe.fd);
=======
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
>>>>>>> main
}



		
		// else if (exe.tmp->meta_char && !ft_strncmp(exe.tmp->meta_char, "<", 1))