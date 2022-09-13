#include "../includes/minishell.h"

void exec_pipe_commands(t_command **prompt, char **envp)
{
	(void)prompt;
	(void)envp;
	int fd[2];
    char * test;

	test = NULL;
	pipe(fd);
	dup2(fd[1], fileno(stdout));
	close(fd[0]);
	close(fd[1]);
}