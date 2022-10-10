/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 12:16:26 by memam             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/09/24 18:53:06 by memam            ###   ########.fr       */
=======
/*   Updated: 2022/09/20 10:59:05 by dpaulino         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(void)
{
	char	command[1000];

	if (getcwd(command, sizeof(command)) != NULL)
<<<<<<< HEAD
		printf("%s\n", command);
	printf("\n");
=======
		printf("%s", command);
	printf("😀😀😀😀😀😀😀\n");
>>>>>>> main
	return (0);
}
