/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 09:42:11 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/14 12:27:42 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*parse_prompt(void)
{
	char	*parser;
	char	current_dir[1024];
	char	*tmp;

	parser = ft_strdup(RED_CLR);
	tmp = ft_strjoin(parser, getenv("USER"));
	free(parser);
	parser = ft_strjoin(tmp, GREEN_CLR);
	free(tmp);
	tmp = ft_strjoin(parser, "@MINISHELL:");
	free(parser);
	parser = ft_strjoin(tmp, BLUE_CLR);
	free(tmp);
	tmp = ft_strjoin(parser, "~");
	free(parser);
	parser = ft_strjoin(tmp, getcwd(current_dir, 1024));
	free(tmp);
	tmp = ft_strjoin(parser, WHITE_CLR);
	free(parser);
	parser = ft_strjoin(tmp, "$ ");
	free(tmp);
	return (parser);
}

void	exit_prompt(char**envp)
{
	free_envp(envp);
	printf("EXIT\n");
	exit(0);
}

void	shell_prompt(char **argv, char **envp)
{
	t_command	*prompt;
	char		*buffer;
	char		*ptr;

	(void)argv;
	while (1)
	{
		ptr = parse_prompt();
		buffer = readline(ptr);
		free(ptr);
		if (buffer && *buffer)
		{
			prompt = malloc(sizeof(t_command));
			struct_init_simple(&prompt, envp);
			if (!buffer_parsing(buffer, &prompt, envp))
				exec_simple(prompt, envp);
			else
				exec_complex(&prompt, envp);
			add_history(buffer);
			free_prompt(&prompt);
		}
		if (!buffer)
			exit_prompt(envp);
		free(buffer);
	}
}
