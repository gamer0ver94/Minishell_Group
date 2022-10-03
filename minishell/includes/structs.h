/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 17:51:34 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/03 13:33:38 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
// main struct where all magic happens
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
//parsing helper to reduce code

typedef struct s_parse
{
	int	i;
	int	j;
	int	l;
	int	lock;
	int	lock_2;
	int	code;
}	t_parse;
//file descriptor struct
typedef struct s_file
{
	int		**fd;
	char	**meta_char;
}	t_file;
//helper to reduce code
typedef struct s_helper
{
	struct s_command	*tmp;
	int					i;
	int					j;
	int					h;
	int					x;
	int					y;
}	t_helper;
//buffer_parsing struct helper to reduce code
typedef struct s_helper2
{
	char	**args;
	char	**exe;
	char	**meta_chars;
	int		code;
	int		i;
}	t_helper2;
//buffer_parsing struct helper to reduce code
typedef struct s_tmp
{
	int		i;
	int		j;
	int		h;
	int		a;
	int		b;
}	t_tmp;
//exec_complex_struct
typedef struct s_execc
{
	t_command	*tmp;
	int			**fd;
	int			**files;
	int			h;
	int			i;
	int			j;
	int			lock;
}	t_execc;
#endif