/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 12:07:34 by dpaulino          #+#    #+#             */
/*   Updated: 2022/08/31 16:22:56 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	logo(char *path)
{
	int		fd;
	char	*logo;

	logo = (char *)ft_calloc(700, sizeof(char *));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (1);
	while (read(fd, logo, 1))
		printf("%s", logo);
	close(fd);
	free((char *)logo);
	return (0);
}
