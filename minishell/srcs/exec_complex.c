/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_complex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:48:05 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/03 10:25:33 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_last_meta(t_command *prompt, t_command *tmp)
{
	t_command	*tmp2;

	tmp2 = prompt;
	while (tmp2)
	{
		if (tmp2->next && tmp2->next->id == tmp->id)
			return (tmp2->meta_char);
		tmp2 = tmp2->next;
	}
	return (NULL);
}

void	wait_childs(t_execc *exe)
{
	while (exe->j > 0)
	{
		waitpid(-1, NULL, 0);
		exe->j--;
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
		if (exe->tmp->meta_char && !ft_strncmp(exe->tmp->meta_char, "|", 1))
			pipef(exe, prompt, envp);
		// else if (exe->tmp->meta_char && !ft_strncmp(exe->tmp->meta_char, ">>", 2))
		// 	redirect_out(exe, prompt, envp);
		else if (exe->tmp->meta_char && !ft_strncmp(exe->tmp->meta_char, ">", 1))
			redirect_out(exe, prompt, envp);
		else if (exe->tmp->meta_char && !ft_strncmp(exe->tmp->meta_char, "<", 1))
			redirect_in(exe, prompt, envp);
		// else if (exe->tmp->meta_char && !ft_strncmp(exe->tmp->meta_char, "<<", 2))
		// 	redirect_in(exe, prompt, envp);	
		else
		{
			last_cmd(exe, prompt, envp);
		}
	}
	close_pipes(prompt, exe->fd);
	wait_childs(exe);
	free_fd(exe, prompt);
}
