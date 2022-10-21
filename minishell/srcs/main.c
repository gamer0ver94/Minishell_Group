/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 12:07:26 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/21 15:28:37 by memam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_status;

int	main(int argc, char **argv, char **envp)
{
	char	**new_envp;

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
