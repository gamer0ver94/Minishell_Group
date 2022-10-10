/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 10:27:32 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/10 13:48:02 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_command	*get_last(t_command *prompt)
{
	t_command	*tmp;

	tmp = prompt;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

void	free_prompt_util(t_command *tmp, int i)
{
	while (tmp->envp[i])
		free(tmp->envp[i++]);
	free(tmp->envp);
}

void	free_prompt(t_command **prompt)
{
	t_command	*tmp;
	t_command	*aux;
	int			i;

	tmp = (*prompt);
	i = 0;
	while (tmp != NULL)
	{
		i = 0;
		free(tmp->cmd);
		free(tmp->meta_char);
		while (tmp->argv && tmp->argv[i])
		{
			free(tmp->argv[i]);
			i++;
		}
		i = 0;
		while (tmp->envp_val[i])
			free(tmp->envp_val[i++]);
		free(tmp->envp_val);
		i = 0;
		while (tmp->envp[i])
			free(tmp->envp[i++]);
		free(tmp->envp);
		free(tmp->argv);
		i = 0;
		aux = tmp;
		tmp = tmp->next;
		free(aux);
	}
}	

void	struct_init_complex(t_command **prompt, char **envp)
{
	t_helper	help;

	init_helper(&help, prompt);
	while (help.tmp->next != NULL)
		help.tmp = help.tmp->next;
	help.tmp->next = malloc(sizeof(t_command));
	help.tmp = help.tmp->next;
	help.tmp->cmd = NULL;
	help.tmp->argc = 0;
	help.tmp->argv = NULL;
	help.tmp->meta_char = NULL;
	help.tmp->next = NULL;
	help.tmp->envp = ft_calloc(500, sizeof(char *));
	help.tmp->envp_val = ft_calloc(1000, sizeof(char *));
	init_envp_complex(&help, envp);
}

void	struct_init_simple(t_command **prompt, char **envp)
{
	t_helper	*help;

	help = malloc(sizeof(t_helper));
	init_helper(help, prompt);
	help->tmp->cmd = NULL;
	help->tmp->argc = 0;
	help->tmp->argv = NULL;
	help->tmp->meta_char = NULL;
	help->tmp->id = 0;
	help->tmp->envp = malloc(sizeof(char *) * 500);
	help->tmp->envp_val = malloc(sizeof(char *) * 1000);
	help->tmp->next = NULL;
	init_envp_simple(help, envp);
	free(help);
}
