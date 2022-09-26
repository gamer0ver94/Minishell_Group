/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 12:16:26 by memam             #+#    #+#             */
/*   Updated: 2022/09/20 10:59:05 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(void)
{
	char	command[1000];

	if (getcwd(command, sizeof(command)) != NULL)
		printf("%s", command);
	printf("😀😀😀😀😀😀😀\n");
	return (0);
}
