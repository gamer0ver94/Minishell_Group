/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 09:42:11 by dpaulino          #+#    #+#             */
/*   Updated: 2022/09/18 13:39:29 by memam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*parse_prompt(void)
{
	char	*parser;
	char	current_dir[1024];
	char	*tmp;

	parser = ft_strdup(BLACK_CLR);
	tmp = ft_strdup(parser);
	free(parser);
	parser = ft_strjoin(tmp, getenv("USER"));
	free(tmp);
	tmp = ft_strjoin(parser, BOLD);
	free(parser);
	parser = ft_strjoin(tmp, GREEN_CLR);
	free(tmp);
	tmp = ft_strjoin(parser, "@MINISHELL:");
	free(parser);
	parser = ft_strjoin(tmp, MAGENTA_CLR);
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

int	shell_prompt(char **argv, char **envp)
{
	t_command	*prompt;
	char		*buffer;
	char		*ptr;
	(void)prompt;
	(void)envp;
	
	
	while (1)
	{
		prompt = malloc(sizeof(t_command));
		ptr = parse_prompt();
		struct_init(&prompt, envp);
		buffer = readline(ptr);
		add_history(buffer);
		// parse_buffer(buffer, &prompt, envp);
		if (ft_strlen(buffer))
		{
			if (!parse_buffer(buffer, &prompt, envp))
			{
				exec_command(prompt, envp);
			}
			/*else
			{
				exec_pipe_commands(&prompt, envp);
			}*/
		}
		if (argv[1] && !ft_strncmp(argv[1], "debugg",6))
			print_struct(prompt);
		free(buffer);
		free(ptr);
		free_prompt(&prompt);
	}
	return (0);
}
