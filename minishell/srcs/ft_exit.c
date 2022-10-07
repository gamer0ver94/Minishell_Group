/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 23:44:25 by memam             #+#    #+#             */
/*   Updated: 2022/10/05 20:10:22 by memam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_exit(char **args)
{
	int	val;

	if (args[2])
	{
		printf("minisell: %s: too many arguments\n", args[0]);
		return (1);
	}
	if (args[1])
	{
		free_args(args);
		val = ft_atoi(args[1]);
		exit (val);
	}
	free_args(args);
	exit(EXIT_SUCCESS);
}
