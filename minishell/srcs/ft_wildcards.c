/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcards.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 00:48:30 by memam             #+#    #+#             */
/*   Updated: 2022/09/25 01:36:06 by memam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_wildcards(char *args)
{
    int     i;
    char    **tmp;

    i = 0;
    tmp = ft_split(args, '*');
    if (!tmp)
        return (1);
    i = 1;
    while (tmp[i])
    {
        
        printf("hi %s\n", tmp[i]);
            i++;
    }
        
    free_tab(tmp);

    return (0);
}