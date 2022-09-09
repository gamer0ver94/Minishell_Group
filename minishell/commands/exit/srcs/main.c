/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 00:30:56 by dpaulino          #+#    #+#             */
/*   Updated: 2022/09/02 18:18:53 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int main (int argc, char **argv, char **envp)
{
    (void)argc;
	(void)argv;
	(void)envp;
    printf("goodbye\n");
    exit (0);
}