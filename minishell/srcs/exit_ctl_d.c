/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_ctl_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 23:47:26 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/16 00:03:05 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_ctl_d(char *ptr, char *buffer, char **envp)
{
	free(ptr);
	if (!buffer)
		exit_prompt(envp);
	free(buffer);
}
