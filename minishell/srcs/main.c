/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 12:07:26 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/15 23:59:03 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_status;

void	sighandler(int signal)
{
	if (signal == SIGQUIT)
	{
		printf("\nThank you for using MINISHELL\n");
		exit(0);
	}
	else if (signal == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	**new_envp;

	(void)argv;
	if (argc > 1)
	{
		printf("No <ARGUMENTS> are needed\n");
		return (1);
	}
	g_status = 2;
	new_envp = ft_calloc(1000, sizeof(char *));
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &sighandler);
	create_env(new_envp, envp);
	logo("assets/logo.txt");
	shell_prompt(new_envp);
	return (0);
}
