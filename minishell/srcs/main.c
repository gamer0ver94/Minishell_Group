/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 12:07:26 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/24 16:05:57 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_status;

void	sighandler(int signal)
{
	if (signal == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		g_status = 130;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char			**new_envp;
	struct termios	term;

	termios_config(&term);
	(void)argv;
	if (argc > 2)
	{
		printf("No <ARGUMENTS> are needed\n");
		return (1);
	}
	g_status = 0;
	new_envp = ft_calloc(1000, sizeof(char *));
	create_env(new_envp, envp);
	logo("assets/logo.txt");
	shell_prompt(new_envp);
	return (0);
}
