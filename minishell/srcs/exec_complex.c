/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_complex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:48:05 by dpaulino          #+#    #+#             */
/*   Updated: 2022/09/30 14:48:18 by dpaulino         ###   ########.fr       */
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

void	last_cmd(t_execc *exe, t_command **prompt, char **envp)
{
	if (!ft_strncmp(get_last_meta((*prompt), exe->tmp), "|", 1))
	{
		if (fork() == 0)
		{
			dup2(exe->fd[exe->i][0], STDIN_FILENO);
			close_pipes(prompt, exe->fd);
			exec_simple(exe->tmp, envp);
			exit (0);
		}
	}
	exe->tmp = exe->tmp->next;
}

void	first_cmd(t_execc *exe, t_command **prompt, char **envp)
{
	if (!ft_strncmp(exe->tmp->meta_char, ">>", 2) && \
	!ft_strncmp(exe->tmp->meta_char, ">>", ft_strlen(exe->tmp->meta_char)))
		redirect_out(exe, prompt, envp);
	else if (!ft_strncmp(exe->tmp->meta_char, ">", 1) && \
	!ft_strncmp(exe->tmp->meta_char, ">", ft_strlen(exe->tmp->meta_char)))
		redirect_out(exe, prompt, envp);
	else if (!ft_strncmp(exe->tmp->meta_char, "<<", 2) && \
	!ft_strncmp(exe->tmp->meta_char, "<<", ft_strlen(exe->tmp->meta_char)))
		redirect_in_complex(exe, prompt, envp);
	else if (!ft_strncmp(exe->tmp->meta_char, "<", 1) && \
	!ft_strncmp(exe->tmp->meta_char, "<", ft_strlen(exe->tmp->meta_char)))
	{
		redirect_in(exe, prompt, envp);
		exe->tmp = NULL;
	}
	else
	{
		if (fork() == 0)
		{
			dup2(exe->fd[exe->i][1], STDOUT_FILENO);
			close_pipes(prompt, exe->fd);
			exec_simple(exe->tmp, envp);
			exit(0);
		}
		exe->tmp = exe->tmp->next;
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
		else if (exe->tmp->meta_char && !ft_strncmp(exe->tmp->meta_char, ">>", 2))
			redirect_out(exe, prompt, envp);
		else if (exe->tmp->meta_char && !ft_strncmp(exe->tmp->meta_char, ">", 1))
			redirect_out(exe, prompt, envp);
		else if (exe->tmp->meta_char && !ft_strncmp(exe->tmp->meta_char, "<", 1))
			redirect_in(exe, prompt, envp);
		else if (exe->tmp->meta_char && !ft_strncmp(exe->tmp->meta_char, "<<", 2))
			redirect_in(exe, prompt, envp);	
		else
		{
			last_cmd(exe, prompt, envp);
		}
			
	}
	close_pipes(prompt, exe->fd);
	wait_childs(exe);
	free_fd(exe, prompt);
}



		
		// else if (exe.tmp->meta_char && !ft_strncmp(exe.tmp->meta_char, "<", 1))