#include "../includes/minishell.h"

void    print_struct(t_command  *prompt)
{
    int i;
	
	t_command *tmp;

	tmp = prompt;
    i = 0;
    printf("_____________TEST____________________\n\n");
	
	while (tmp->envp[i])
	{
		printf("envp[%d] -> %s\n",i,tmp->envp[i]);
		i++;
	}
	i = 0;
	while (tmp->envp[i])
	{
		printf("envp_values[%d] -> %s\n",i,tmp->envp_val[i]);
		i++;
	}
	i = 0;
	printf("command -> %s\n",tmp->cmd);
    printf("argc -> %d\n",tmp->argc);
	while (tmp)
	{
		while (tmp->argv[i])
    	{
			if (tmp->argv[i][0])
      	 		printf("argv[%d] -> %s\n",i, tmp->argv[i]);
     	   i++;
   		}
		i = 0;
		tmp = prompt->next;
	}
	// printf("%s",tmp->next->argv[0]);
     printf("____________OUTPUT___________________\n\n");
}