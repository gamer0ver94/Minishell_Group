/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 09:42:11 by dpaulino          #+#    #+#             */
/*   Updated: 2022/09/09 09:12:02 by dpaulino         ###   ########.fr       */
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
	return (parser);
}

void struct_init(t_command **prompt, char **envp)
{
	int i;
	int j;
	int h = 0;
	i = 0;
	j = 0;
	(*prompt)->cmd = NULL;
	(*prompt)->argc = 0;
	(*prompt)->argv = NULL;
	(*prompt)->next = NULL;
	(*prompt)->envp = ft_calloc(100, sizeof(char *));
	(*prompt)->envp_val = ft_calloc(100, sizeof(char *));
	while (envp[i])
	{
		(*prompt)->envp[i] = ft_calloc(100, sizeof(char));
		while (envp[i][j] != '=')
		{
			(*prompt)->envp[i][j] = envp[i][j];
			j++;
		}
		(*prompt)->envp_val[i] = ft_calloc(100, sizeof(char));
		j++;
		while(envp[i][j])
		{
			(*prompt)->envp_val[i][h] = envp[i][j];
			j++;
			h++;
		}
		h = 0;
		j = 0;
		i++;
	}
	(*prompt)->envp[i] = NULL;
	(*prompt)->envp_val[i] = NULL;
}

void	free_prompt(t_command **prompt)
{
	int	i;

	i = 0;
	if ((*prompt)->cmd)
		free((*prompt)->cmd);
	if ((*prompt)->argv)
	{
		while ((*prompt)->argv[i])
		{
			free((*prompt)->argv[i]);
			i++;
		}
	}
	free((*prompt)->argv);
	i = 0;
	if ((*prompt)->envp)
	{
		while ((*prompt)->envp[i])
		{
			free((*prompt)->envp[i]);
			i++;
		}
	}
	free((*prompt)->envp);
	i = 0;
	if ((*prompt)->envp_val)
	{
		while ((*prompt)->envp_val[i])
		{
			free((*prompt)->envp_val[i]);
			i++;
		}
	}
	free((*prompt)->envp_val);
}

int	get_prompt(char **envp)
{
	t_command	*prompt;
	char		*buffer;
	char		*ptr;

	prompt = malloc(sizeof(t_command));
	while (1)
	{
		ptr = parse_prompt();
		struct_init(&prompt, envp);
		buffer = readline("MiniShell: $ ");
		add_history(buffer);
		if (ft_strlen(buffer))
		{
			if (!parse_buffer(buffer, &prompt, envp))
			{
				print_struct(prompt);
				exec_command(prompt, envp);
			}
		}
		free(buffer);
		free(ptr);
		free_prompt(&prompt);
	}
	return (0);
}
