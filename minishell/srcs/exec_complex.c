/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_complex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:48:05 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/12 21:57:07 by dpaulino         ###   ########.fr       */
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

int	count_files(t_command **prompt)
{
	t_command	*tmp;
	int			i;

	i = 0;
	tmp = (*prompt);
	while (tmp)
	{
		if (tmp->meta_char && !ft_strncmp(tmp->meta_char, ">", 1))
			i++;
		else if (tmp->meta_char && !ft_strncmp(tmp->meta_char, ">>", 2))
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void	wait_childs(t_execc *exe)
{
	int	i;

	i = 0;
	while (i < exe->g)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
	write(2, "waiting\n", 8);
}

void	open_files(t_command **prompt, int **file)
{
	int	i;

	i = 0;
	while (i < count_files(prompt))
	{
		if (pipe(file[i]) == -1)
			write(2, "error opening pipe\n", 19);
		i++;
	}
}

void	close_files(t_command **prompt, int **file)
{
	int	i;

	i = 0;
	while (i < count_files(prompt))
	{
		if (close(file[i][0]) == -1)
			write(2, "error opening pipe\n", 19);
		if (close(file[i][1]) == -1)
			write(2, "error opening pipe\n", 19);
		i++;
	}
}

void	alloc_files(t_execc *exe, t_command **prompt)
{
	int	i;

	i = 0;
	exe->files = malloc(sizeof(int *) * count_files(prompt));
	while (count_files(prompt) > i)
	{
		exe->files[i] = malloc(sizeof(int) * 2);
		pipe(exe->files[i]);
		i++;
	}
}

void	free_files(t_execc *exe, t_command **prompt)
{
	int	i;

	i = 0;
	(void)prompt;
	while (i < count_files(prompt) && exe->files[i])
	{
		free(exe->files[i]);
		i++;
	}
	if (exe->files)
		free(exe->files);
}

void	exec_complex(t_command **prompt, char **envp)
{
	t_execc		*exe;
	
	exe = malloc(sizeof(t_execc));
	init_execc_struct(exe, prompt);
	while (exe->tmp)
	{
		if (exe->tmp->meta_char && !ft_strncmp(exe->tmp->meta_char, "|", 1))
			pipef(exe, prompt, envp);
		else if (exe->tmp->meta_char && !ft_strncmp(exe->tmp->meta_char, ">>", 2))
			redirect_out(exe, prompt, envp);
		else if (exe->tmp->meta_char && !ft_strncmp(exe->tmp->meta_char, ">", 1))
			redirect_out(exe, prompt, envp);
		else if (exe->tmp->meta_char && !ft_strncmp(exe->tmp->meta_char, "<<", 2))
			redirect_in_complex(exe, prompt, envp);
		else if (exe->tmp->meta_char && !ft_strncmp(exe->tmp->meta_char, "<", 1))
			redirect_in(exe, prompt, envp);	
		else
			last_cmd(exe, prompt, envp);
	}
	close_pipes(prompt, exe->fd);
	close_files(prompt, exe->files);
	wait_childs(exe);
	free_fd(exe, prompt);
	free_files(exe, prompt);
	free(exe->pid);
	free(exe);
	return ;
}
