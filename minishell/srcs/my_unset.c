#include "../includes/minishell.h"

void	my_unset(t_command *prompt, char **envp)
{
	int i;
	int j;
	int h;

	h = 0;
	j = 0;
	i = 0;
	while(prompt->argv[i])
	{
		while (ft_strncmp(prompt->envp[j], prompt->argv[i], ft_strlen(prompt->envp[j])))
		{
			if (!ft_strncmp(prompt->envp[j], prompt->argv[i], ft_strlen(prompt->envp[j])))
			{
				ft_bzero(envp[h], ft_strlen(envp[h]));
				exit(0);
			}
			j++;
		}
		j = 0;
		i++;
	}
}