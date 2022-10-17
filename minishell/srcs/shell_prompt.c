/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 09:42:11 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/17 16:59:42 by dpaulino         ###   ########.fr       */
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

void	add_hist_free_prompt(t_command *prompt, char *buffer)
{
	add_history(buffer);
	free_prompt(&prompt);
}

void	shell_prompt(char **envp)
{
	t_command	*prompt;
	char		*buffer;
	char		*ptr;
	int			res;

	while (1)
	{
		ptr = parse_prompt();
		buffer = readline(ptr);
		free(ptr);
		if (buffer && *buffer)
		{
			prompt = malloc(sizeof(t_command));
			struct_init_simple(&prompt, envp);
			res = buffer_parsing(buffer, &prompt, envp);
			if (res == -2)
				write (2, "MiNiShEeL : error <QUOTES NOT CLOSED>\n", 38);
			else if (res == 0)
				exec_simple(prompt, envp);
			else
				exec_complex(&prompt, envp);
			add_hist_free_prompt(prompt, buffer);
		}
		exit_ctl_d(buffer, envp);
	}
}
