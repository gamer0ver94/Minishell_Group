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
	int fd[2];
	int *pid;
	t_command *tmp;
	int	i;

	i = 0;
	pid = malloc(sizeof(int) * count_pipes(prompt));
	tmp = (*prompt);
	if(pipe(fd) == -1)
		printf("pipe error\n");
	pid[i] = fork();
	if (pid[i] == -1)
		printf("ups no fork here");
	if (pid[i] == 0)
	{
		dup2(fd[1],STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		exec_command(tmp, envp);
	}
	tmp = tmp->next;
	i++;
	while(tmp)
	{
		// tmp = tmp->next;
		// i++;
		pid[i] = fork();
		printf("%d\n", i);
		if (pid[i] == -1)
			printf("ups no fork here");
		if (pid[i] == 0)
		{
			dup2(fd[0],STDIN_FILENO);
			close(fd[0]);
			close(fd[1]);
			exec_command(tmp,envp);
		}
		else
		{
			tmp = tmp->next;
			waitpid(pid[i],NULL, 0);
		}
	}
	i = 0;
	close(fd[0]);
	close(fd[1]);
	free(pid);

}