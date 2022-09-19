/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 12:43:46 by dpaulino          #+#    #+#             */
/*   Updated: 2022/09/19 13:31:07 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_helper(t_helper *helper, t_command **prompt)
{
	helper->tmp = (*prompt);
	helper->i = 0;
	helper->j = 0;
	helper->h = 0;
	helper->x = 0;
	helper->y = 0;
}
