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

void	exec_pipe_commands(t_command **prompt, char **envp)
{

	(void)prompt;
	(void)envp;

}