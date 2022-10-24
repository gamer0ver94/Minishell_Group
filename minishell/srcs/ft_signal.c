/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 22:32:59 by memam             #+#    #+#             */
/*   Updated: 2022/10/24 15:50:22 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_handler(int sig)
{
	g_status = 130;
	if (sig == SIGQUIT)
	{
		printf("\nThank you for using MINISHELL\n");
		exit(0);
	}
	else if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ctrl_c(int sig)
{
	g_status = 130;
	write(1, "\n", 1);
	(void)sig;
}

void	back_slash(int sig)
{
	g_status = 131;
	printf("Quit: 3\n");
	(void)sig;
}

void	get_signals(int sig)
{
	if (sig == 1)
	{
		signal(SIGINT, sighandler);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 2)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, back_slash);
	}
}

void	sighandler2(int sig)
{
	if (sig == SIGQUIT)
	{
		printf("^\\QUIT\n");
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &sighandler);
		g_status = 131;
	}
	else if (sig == SIGINT)
	{
		printf("\n");
		g_status = 130;
		signal(SIGINT, &sighandler);
		signal(SIGQUIT, SIG_IGN);
	}
}
