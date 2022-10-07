/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 12:43:46 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/07 09:18:21 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_helper(t_helper *helper, t_command **prompt)
{
	helper->tmp = (*prompt);
	helper->i = 0;
	helper->j = 0;
	helper->h = 0;
	helper->x = 0;
	helper->y = 0;
}

void	init_envp_complex(t_helper *help, char **envp)
{
	while (envp[help->i])
	{
		help->tmp->envp[help->i] = ft_calloc(1000, sizeof(char));
		while (envp[help->i][help->j] != '=')
		{
			help->tmp->envp[help->i][help->j] = envp[help->i][help->j];
			help->j++;
		}
		help->tmp->envp[help->i][help->j] = '\0';
		help->tmp->envp_val[help->i] = ft_calloc(5000, sizeof(char));
		help->j++;
		while (envp[help->i][help->j])
		{
			help->tmp->envp_val[help->i][help->h] = envp[help->i][help->j];
			help->j++;
			help->h++;
		}
		help->tmp->envp_val[help->i][help->j] = '\0';
		help->h = 0;
		help->j = 0;
		help->i++;
	}
	help->tmp->envp[help->i] = NULL;
	help->tmp->envp_val[help->i] = NULL;
}

void	init_envp_simple(t_helper *help, char **envp)
{
	while (envp[help->i])
	{
		help->tmp->envp[help->i] = ft_calloc(1000, sizeof(char));
		while (envp[help->i][help->j] != '=')
		{
			help->tmp->envp[help->i][help->j] = envp[help->i][help->j];
			help->j++;
		}
		help->tmp->envp[help->i][help->j] = '\0';
		help->tmp->envp_val[help->i] = ft_calloc(5000, sizeof(char));
		help->j++;
		while (envp[help->i][help->j])
		{
			help->tmp->envp_val[help->i][help->h] = envp[help->i][help->j];
			help->j++;
			help->h++;
		}
		help->tmp->envp_val[help->i][help->j] = '\0';
		help->h = 0;
		help->j = 0;
		help->i++;
	}
	help->tmp->envp[help->i] = NULL;
	help->tmp->envp_val[help->i] = NULL;
}
