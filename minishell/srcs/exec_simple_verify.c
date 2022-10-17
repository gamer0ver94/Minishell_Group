/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_verify.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:36:48 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/17 16:37:04 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	verify_access(t_command *prompt)
{
	if (access(prompt->cmd, F_OK) == 0)
	{
		write(2, prompt->cmd, ft_strlen(prompt->cmd));
		write(2, ": is a directory\n", 17);
		exit(126);
	}
	else
	{
		write(2, prompt->cmd, ft_strlen(prompt->cmd));
		write(2, ": command not found\n", 20);
		exit(127);
	}
}
