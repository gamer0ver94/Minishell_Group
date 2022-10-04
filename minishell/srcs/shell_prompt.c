/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 09:42:11 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/03 14:22:55 by memam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*parse_prompt(void)
{
	char	*parser;
	//char	current_dir[1024];
	char	*tmp;

	parser = NULL;
	//parser = ft_strdup(getenv("USER"));
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
	//parser = ft_strjoin(tmp, getcwd(current_dir, 1024));
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
	while (1)
	{
		
		prompt = malloc(sizeof(t_command));
		ptr = parse_prompt();
		struct_init_simple(&prompt, envp);
		buffer = readline("MINISHELL $ ");
		add_history(buffer);
		if (ft_strlen(buffer))
		{
			if (!buffer_parsing(buffer, &prompt, envp))
				exec_simple(prompt, envp);
			//else
				// exec_complex(&prompt, envp);
			
		}
		if (argv[1] && !ft_strncmp(argv[1], "debugg", 6))
			print_struct(prompt);
		free(buffer);
		free(ptr);
		if (prompt->argc)
			free_prompt(&prompt);
		
	}
	return (0);
}
