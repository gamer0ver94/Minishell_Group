/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 10:27:32 by dpaulino          #+#    #+#             */
/*   Updated: 2022/09/19 13:31:14 by dpaulino         ###   ########.fr       */
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

void	free_prompt(t_command **prompt)
{
	t_command	*tmp;
	t_command	*aux;
	int			i;

	tmp = (*prompt);
	i = 0;
	while (tmp)
	{
		if (tmp->cmd)
			free(tmp->cmd);
		while (tmp && tmp->argv[i])
		{
			if (tmp->argv[i])
				free(tmp->argv[i]);
			i++;
		}
		free(tmp->argv);
		i = 0;
		if (tmp->envp)
		{
			while (tmp->envp[i])
				free(tmp->envp[i++]);
			free(tmp->envp);
		}
		i = 0;
		if (tmp->envp_val)
		{
			while (tmp->envp_val[i])
				free(tmp->envp_val[i++]);
		}
		free(tmp->envp_val);
		aux = tmp;
		tmp = tmp->next;
		free(aux);
		i = 0;
	}
}	

void struct_init2(t_command **prompt, char **envp)
{
	t_command *tmp;
	int i;
	int j;
	int h;
	
	h = 0;
	i = 0;
	j = 0;
	(void)h;
	(void)j;
	(void)i;
	(void)envp;
	tmp = (*prompt);
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = malloc(sizeof(t_command));
	tmp = tmp->next;
	tmp->cmd = NULL;
	tmp->argc = 0;
	tmp->argv = NULL;
	tmp->meta_char = NULL;
	tmp->next = NULL;
	tmp->envp = ft_calloc(500, sizeof(char *));
	tmp->envp_val = ft_calloc(1000, sizeof(char *));
	while (envp[i])
	{
		tmp->envp[i] = ft_calloc(1000, sizeof(char));
		while (envp[i][j] != '=')
		{
			tmp->envp[i][j] = envp[i][j];
			j++;
		}
		tmp->envp[i][j] = '\0';
		tmp->envp_val[i] = ft_calloc(5000, sizeof(char));
		j++;
		while (envp[i][j])
		{
			tmp->envp_val[i][h] = envp[i][j];
			j++;
			h++;
		}
		tmp->envp_val[i][j] = '\0';
		h = 0;
		j = 0;
		i++;
	}
	tmp->envp[i] = NULL;
	tmp->envp_val[i] = NULL;
}

void struct_init(t_command **prompt, char **envp)
{
	t_helper help;

	(void)envp;
	init_helper(&help, prompt);

	help.tmp = (*prompt);
	help.tmp->cmd = NULL;
	help.tmp->argc = 0;
	help.tmp->argv = NULL;
	help.tmp->meta_char = NULL;
	help.tmp->id = 0;
	help.tmp->envp = ft_calloc(500, sizeof(char *));
	help.tmp->envp_val = ft_calloc(1000, sizeof(char *));
	help.tmp->next = NULL;
	while (envp[help.i])
	{
		help.tmp->envp[help.i] = ft_calloc(1000, sizeof(char));
		while (envp[help.i][help.j] != '=')
		{
			help.tmp->envp[help.i][help.j] = envp[help.i][help.j];
			help.j++;
		}
		help.tmp->envp[help.i][help.j] = '\0';
		help.tmp->envp_val[help.i] = ft_calloc(5000, sizeof(char));
		help.j++;
		while (envp[help.i][help.j])
		{
		help.tmp->envp_val[help.i][help.h] = envp[help.i][help.j];
			help.j++;
			help.h++;
		}
		help.tmp->envp_val[help.i][help.j] = '\0';
		help.h = 0;
		help.j = 0;
		help.i++;
	}
	help.tmp->envp[help.i] = NULL;
	help.tmp->envp_val[help.i] = NULL;
}
