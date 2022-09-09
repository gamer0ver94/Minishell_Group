/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 00:27:32 by dpaulino          #+#    #+#             */
/*   Updated: 2022/09/02 23:59:03 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
    (void)argc;
	(void)argv;
	(void)envp;
    printf("%s\n",getenv("PWD"));
    return (0);
}