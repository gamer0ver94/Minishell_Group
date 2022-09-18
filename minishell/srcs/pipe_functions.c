/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 16:37:32 by dpaulino          #+#    #+#             */
/*   Updated: 2022/09/18 23:57:32 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_last_meta(t_command *prompt, t_command *tmp)
{
	t_command *tmp2;

	tmp2 = prompt;
	while(tmp2)
	{
		if(tmp2->next && tmp2->next->id == tmp->id)
			return (tmp2->meta_char);
		tmp2 = tmp2->next;
	}
	return (NULL);
}

void f_and(t_command **prompt, t_command *tmp, char **envp, int **fd, int i)
{
	if (get_last_meta((*prompt),tmp) && !ft_strncmp(get_last_meta((*prompt),tmp), "|", 1))
	{
		if (fork() == 0)
		{
			if (dup2(fd[i][0], STDIN_FILENO) < 0)
			{
				printf("error\n");
				exit(1);
			}
			close_pipes(prompt,fd);
			exec_command(tmp, envp);
			exit(0);
		}
	}
	else
	{
		exec_command(tmp, envp);
	}
	
	
}


void f_pipe(t_command **prompt, t_command *tmp, char **envp, int **fd, int i)
{
	if (get_last_meta((*prompt),tmp) && \
	!ft_strncmp(get_last_meta((*prompt),tmp), "&&", 2))
	{
		if (tmp->meta_char && !ft_strncmp(tmp->meta_char, "|", 1))
		{
			if (fork() == 0)
			{
				dup2(fd[i][1], STDOUT_FILENO);
				exec_command(tmp,envp);
				close_pipes(prompt, fd);
				exit(0);
			}
		}
		else
			exec_command(tmp, envp);
	}
	else
	{
		if (fork() == 0)
		{
			if (dup2(fd[i][0], STDIN_FILENO) < 0)
			{
				printf("error\n");
				exit(1);
			}
			if (tmp->id != 1 && tmp->meta_char != NULL)
			{
				if (dup2(fd[i + 1][1], STDOUT_FILENO) < 0)
				{
					printf("error\n");
					exit(1);
				}
			}
			close_pipes(prompt,fd);
			exec_command(tmp, envp);
			exit(0);
		}
	}	
}