/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 12:07:26 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/10 17:31:44 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_status;

void	sighandler(int signal)
{
	if (signal == SIGSEGV)
	{
		printf("\nThank you for using MINISHELL\n");
		exit(0);
	}
	else if (signal == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		// rl_replace_line("", 0);
		rl_on_new_line();
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)envp;
	(void)argv;
	signal(SIGSEGV, &sighandler);
	signal(SIGQUIT, SIG_IGN);
	// signal(SIGINT, &sighandler);
	if (argc > 2)
	{
		printf("no need argv\n");
		return (1);
	}
	logo("assets/logo.txt");
	shell_prompt(argv, envp);
	return (0);
}
