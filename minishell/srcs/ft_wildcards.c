/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcards.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 00:48:30 by memam             #+#    #+#             */
/*   Updated: 2022/09/26 12:08:12 by memam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_wildcards(char *args)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = ft_split(args, '*');
	if (!tmp)
		return (1);
	i = 0;
	char *name = tmp[0];
	if (name[i] && tmp[1] == NULL)
	{
		while (name[i] != '\0')
		{
			printf("it ok\n");
			i++;
		}
		printf("tmp[0] %s\n", name);
	}
	else
	{
		int		index;

		index = 0;
		while (tmp[1][index])
		{
			if (tmp[1][index] == '.')
				printf("i be one file\n");
			else if (ft_isalnum(tmp[1][index]) != 0)
				printf("i be one répertoire\n");
			index++;
		}
	}
	free_tab(tmp);
	return (0);
}
