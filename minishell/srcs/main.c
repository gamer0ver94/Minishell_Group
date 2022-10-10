/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 12:07:26 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/10 15:18:09 by dpaulino         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	(void)envp;
	(void)argv;

	signal(SIGSEGV, &sighangler);
	signal(SIGQUIT, &sighangler);
	if (argc > 2)
	{
		printf("no need argv\n");
		return (1);
	}
	logo("assets/logo.txt");
	shell_prompt(argv, envp);
	return (0);
}
