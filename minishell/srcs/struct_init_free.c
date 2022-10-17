/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:56:03 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/17 16:57:26 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_helper(t_command *tmp, t_command *aux, int i)
{
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
