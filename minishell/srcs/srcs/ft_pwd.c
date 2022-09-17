/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 12:16:26 by memam             #+#    #+#             */
/*   Updated: 2022/09/15 14:52:32 by memam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(void)
{
	char	command[1000];

	if (getcwd(command, sizeof(command)) != NULL)
		printf("%s\n", command);
	printf("😀😀😀😀😀😀😀");
	return (0);
}
