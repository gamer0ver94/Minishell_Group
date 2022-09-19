/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 22:28:16 by dpaulino          #+#    #+#             */
/*   Updated: 2022/09/19 22:29:59 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_struct(t_command *prompt)
{
	int			i;
	t_command	*tmp;

	tmp = prompt;
	i = 0;
	printf("_____________OUTPUTED____________________\n\n");
	while (tmp != NULL)
	{
		printf("id -> %d\n", tmp->id);
		printf("command -> %s\n", tmp->cmd);
		printf("argc -> %d\n", tmp->argc);
		while (tmp->argv[i])
		{
			if (tmp->argv[i][0])
				printf("argv[%d] -> %s\n", i, tmp->argv[i]);
			i++;
		}
		if (tmp->meta_char)
			printf("meta_char -> %s\n", tmp->meta_char);
		printf("_____________________________\n\n");
		i = 0;
		tmp = tmp->next;
	}
	printf("_____________TESTED_____________\n");
}
