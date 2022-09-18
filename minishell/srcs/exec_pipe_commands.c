#include "../includes/minishell.h"

int count_pipes(t_command **prompt)
{
	t_command *tmp;
	int i;

	i = 0;
	tmp = (*prompt);
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void close_pipes(t_command **prompt, int **fd)
{
	int i;

	i = 0;
	while (i < count_pipes(prompt) - 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

void open_pipes(t_command **prompt, int **fd)
{
	int i;

	i = 0;
	while (i < count_pipes(prompt) - 1)
	{
		fd[i] = malloc(sizeof(int) * 2);
		if (pipe(fd[i]))
			printf("pipe[%d] did not open", i);
		i++;
	}
}


void free_fd(t_command **prompt, int **fd)
{
	int i;

	i = 0;
	while (i < count_pipes(prompt) - 1)
	{
		free(fd[i]);
		i++;
	}
}


//cat ToDo | grep acess | wc
void exec_pipe_commands(t_command **prompt, char **envp)
{
	t_command *tmp;
	int **fd;
	int i;
	int j;
	int lock;

	lock = 0;
	j = count_pipes(prompt) + 1;
	i = 0;
	fd = malloc(sizeof(int) * count_pipes(prompt) - 1);
	open_pipes(prompt, fd);
	tmp = (*prompt);
	
	while (tmp)
	{
		if (tmp->id == 1 && ft_strncmp(tmp->meta_char, "&&", 2))
		{
			if(fork() == 0)
			{
				dup2(fd[i][1], STDOUT_FILENO);
				close_pipes((prompt), fd);
				exec_command(tmp, envp);
				exit(0);
			}
			lock++;
			tmp = tmp->next;
		}
		if (tmp->meta_char && !ft_strncmp(tmp->meta_char, "|", 1))
		{
			f_pipe(prompt, tmp,envp, fd, i);
			lock++;
		}
		else if (tmp->meta_char && !ft_strncmp(tmp->meta_char, "&&", 1))
		{
			f_and(prompt, tmp,envp, fd, i);
		}
		else
		{
			if (lock > 0 || (get_last_meta((*prompt), tmp) && !ft_strncmp(get_last_meta((*prompt),tmp), "|", 1)))
			{
				if (fork() == 0)
				{
					if(dup2(fd[i][0], STDIN_FILENO) < 0) //echo a && ls | wc bug
					{
						printf("error <else condition\n");
						exit(1);
					}
					close_pipes(prompt,fd);
					exec_command(tmp, envp);
					exit(0);
				}
			}
			else
			{
				if (fork() == 0)
				{
					exec_command(tmp, envp);
					close_pipes(prompt, fd);
					exit(0);
				}
				lock = 0;
			}
		}
		tmp = tmp->next;
		i++;
	}
	close_pipes(prompt, fd);
	free_fd(prompt, fd);
	while(j-- > 0)
	{
		waitpid(-1, NULL, 0);
	}
}
	