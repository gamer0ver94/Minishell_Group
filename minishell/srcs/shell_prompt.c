/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 09:42:11 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/10 10:02:26 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

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
	tmp = ft_strjoin(parser , WHITE_CLR);
	free(parser);
	parser = ft_strjoin(tmp, "$ ");
	free(tmp);
	return (parser);
}

int	shell_prompt(char **argv, char **envp)
{
	t_command	*prompt;
	char		*buffer;
	char		*ptr;


	g_status = 0;
	while (1)
	{
		ptr = parse_prompt();
		buffer = readline(ptr);
		if (*buffer)
		{
			prompt = malloc(sizeof(t_command));
			struct_init_simple(&prompt, envp);
			if (!buffer_parsing(buffer, &prompt, envp))
				exec_simple(prompt, envp);
			else
				exec_complex(&prompt, envp);
			add_history(buffer);
			if (argv[1] && !ft_strncmp(argv[1], "debugg", 6))
				print_struct(prompt);
			free_prompt(&prompt);
		}
		free(buffer);
		free(ptr);
	}
	return (0);
}
