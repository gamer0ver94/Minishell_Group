#include "../includes/minishell.h"

void    print_struct(t_command  *prompt)
{
    int i;

    i = 0;
    printf("_____________TEST____________________\n\n");
    printf("command -> %s\n",prompt->cmd);
    printf("argc -> %d\n",prompt->argc);
    while (prompt->argv[i])
    {
        printf("argv[%d] -> %s\n",i, prompt->argv[i]);
        i++;
    }
	i = 0;
	while (prompt->envp[i])
	{
		printf("envp[%d] -> %s\n",i,prompt->envp[i]);
		i++;
	}
	i = 0;
	while (prompt->envp[i])
	{
		printf("envp_values[%d] -> %s\n",i,prompt->envp_val[i]);
		i++;
	}
     printf("____________OUTPUT___________________\n\n");
}