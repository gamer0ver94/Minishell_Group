/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 17:51:34 by dpaulino          #+#    #+#             */
/*   Updated: 2022/09/18 21:11:20 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_command
{
	char				*cmd;
	int					argc;
	char				**argv;
	char				**envp;
	char				**envp_val;
	char				*meta_char;
	int					id;
	struct s_command	*next;
}	t_command;

typedef struct s_parse
{
	int	i;
	int	j;
	int	l;
	int	lock;
	int	lock_2;
}	t_parse;

typedef struct s_file
{
	int		**fd;
	char	**meta_char;
}	t_file;

typedef struct s_helper
{
	struct s_command	*tmp;
	int					i;
	int					j;
	int					h;
	int					x;
	int					y;
}	t_helper;
#endif