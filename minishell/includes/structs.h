/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 17:51:34 by dpaulino          #+#    #+#             */
/*   Updated: 2022/09/19 00:05:47 by memam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_command
{
	char	*cmd;
	int		argc;
	char	**argv;
	char	**envp;
	char	**envp_val;
	struct s_command	*next;
}   t_command;

typedef struct s_parse
{
	int	i;
	int	j;
	int	l;
	int	lock;
	int lock_2;
}	t_parse;