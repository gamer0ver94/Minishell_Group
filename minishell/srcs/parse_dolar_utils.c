/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dolar_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:27:00 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/13 18:29:51 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	identify_dolar(t_command **prompt, char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
	{
		if (args[i][0] && find_char(args[i], "&"))
			get_dolar_char(prompt, args, i);
		i++;
	}
}
