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
     printf("____________OUTPUT___________________\n\n");
}