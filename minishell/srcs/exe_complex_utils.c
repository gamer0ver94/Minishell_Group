/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_complex_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:10:00 by dpaulino          #+#    #+#             */
/*   Updated: 2022/09/22 15:55:18 by dpaulino         ###   ########.fr       */
=======
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:10:00 by dpaulino          #+#    #+#             */
/*   Updated: 2022/09/23 11:51:34 by dpaulino         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_pipes(t_command **prompt)
{
	t_command	*tmp;
	int			i;

	i = 0;
	tmp = (*prompt);
	while (tmp)
	{
<<<<<<< HEAD
		if (tmp->meta_char)
=======
		if (tmp->meta_char && !ft_strncmp(tmp->meta_char, "|", 1))
>>>>>>> main
			i++;
		tmp = tmp->next;
	}
	return (i);
}

<<<<<<< HEAD
void	free_fd(t_command **prompt, int **fd)
{
	int	i;

	i = 1;
	while (i < count_pipes(prompt))
	{
		if (fd[i])
			free(fd[i]);
		i++;
	}
	if (fd)
		free(fd);
=======
void	free_fd(t_execc *exe, t_command **prompt)
{
	int	i;

	i = 0;
	(void)prompt;
	while (i < exe->j && exe->fd[i])
	{
		free(exe->fd[i]);
		i++;
	}
	if (exe->fd)
		free(exe->fd);
}

void	alloc_fd(t_execc *exe, t_command **prompt)
{
	int	i;

	i = 0;
	(void)prompt;
	while (i < exe->j)
	{
		exe->fd[i] = malloc(sizeof(int) * 2);
		if (!exe->fd[i])
			printf("error alocation mem\n");
		i++;
	}
>>>>>>> main
}

void	open_pipes(t_command **prompt, int **fd)
{
	int	i;

	i = 0;
	while (i < count_pipes(prompt))
	{
<<<<<<< HEAD
		if (fd)
			fd[i] = malloc(sizeof(int) * 2);
		if (pipe(fd[i]) == -1)
			printf("pipe[%d] did not open", i);
		i++;
	}
	printf("open pipe %d\n",i);
=======
		if (pipe(fd[i]) == -1)
			write(2, "error opening pipe\n", 19);
		i++;
	}
>>>>>>> main
}

void	close_pipes(t_command **prompt, int **fd)
{
	int	i;

	i = 0;
	(void)prompt;
<<<<<<< HEAD
	while (fd[i])
	{
		if (fd[i])
		{
			if(close(fd[i][0]) == -1)
				printf("error to close fd 0\n");
			else
				printf("closed pipe 0\n");
			if(close(fd[i][1]) == -1)
				printf("error to close fd 1\n");
			else
				printf("closed pipe 1\n");
			printf("_________________");
		}
=======
	while (i < count_pipes(prompt))
	{
		if (close(fd[i][0]) == -1)
			write(2, "error opening pipe\n", 19);
		if (close(fd[i][1]) == -1)
			write(2, "error opening pipe\n", 19);
>>>>>>> main
		i++;
	}
}

void	init_execc_struct(t_execc *exe, t_command **prompt)
{
	exe->tmp = (*prompt);
	exe->lock = 0;
	exe->j = count_pipes(prompt);
	exe->i = 0;
<<<<<<< HEAD
	exe->fd = malloc(sizeof(int) * count_pipes(prompt));
=======
	exe->fd = malloc(sizeof(int *) * exe->j);
	alloc_fd(exe, prompt);
>>>>>>> main
	open_pipes(prompt, exe->fd);
}
