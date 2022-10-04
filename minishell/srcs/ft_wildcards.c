/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcards.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 00:48:30 by memam             #+#    #+#             */
/*   Updated: 2022/10/01 15:26:42 by memam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
//opendir, readdir, closedir
char	**get_list_repertoire(char *rep_courant)
{
	DIR				*dir;
	struct dirent	*list;
	char			**my_list;
	int				i, c;

	i = 0;
	c = 0;
	my_list = NULL;
	list = NULL;
	dir = opendir(rep_courant);
	if (dir == NULL)
	{
		perror("opendir");
		return (NULL);
	}
	while ((list = readdir(dir)) != NULL)
	{
		my_list[i] = list->d_name;
		my_list[i] = ft_strjoin(list->d_name, "");
		i++;
	}
	printf("%s\n", my_list[2]);

	return (my_list);
}

int	ft_wildcards(char *args)
{
	char	*rep_courant;
	char	**list;

	rep_courant = ".";
	if (!args)
		return (1);
	list = get_list_repertoire(rep_courant);
	
	
	
	
	return (0);
}
