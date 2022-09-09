/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 09:51:02 by dpaulino          #+#    #+#             */
/*   Updated: 2022/03/10 09:51:02 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*lastlst;

	if (*lst)
	{
		while (*lst)
		{
			lastlst = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = lastlst;
		}
		*lst = NULL;
	}
}
