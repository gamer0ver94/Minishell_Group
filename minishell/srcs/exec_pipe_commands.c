#include "../includes/minishell.h"

int	count_pipes(t_command **prompt)
{
	t_command *tmp;
	int			i;

	i = 0;
	tmp = (*prompt);
	while(tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void exec_pipe_commands(t_command **prompt, char **envp)
{
	(void)prompt;
	(void)envp;
	int fd[2];
	pid_t pid;
	pid_t pid2;
	t_command *tmp;

	tmp = (*prompt);
	if(pipe(fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		exec_command(tmp, envp);
	}
	else
	{

	}
		pid2 = fork();
		tmp = tmp->next;
		if (pid2 == -1)
			exit(0);
		if (pid2 == 0)
		{
			dup2(fd[0], STDIN_FILENO);
			close(fd[1]);
			close(fd[0]);
			exec_command(tmp, envp);
		}
		else
		{
			tmp = tmp->next;
			if(waitpid(pid, NULL, 0) == -1)
				printf("waiting problem\n");
			if(waitpid(pid2, NULL, 0) == -1)
				printf("waiting problem\n");
			close(fd[0]);
			close(fd[1]);
		}
		

	
}