/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:22:20 by memam             #+#    #+#             */
/*   Updated: 2022/10/06 16:32:57 by memam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void sighangler(int signal)
{
	if (signal == SIGSEGV)
	{
		printf("\nThank you for using MINISHELL\n");
		exit (0);
	}
	if (signal == SIGQUIT)
		(void)signal;
}


void	sigint_handler(int sig)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void) sig;
}

void	ft_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGSEGV, sighangler);
	signal(SIGQUIT, SIG_IGN);
}
