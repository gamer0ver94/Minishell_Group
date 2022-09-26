/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 13:25:13 by dpaulino          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/09/26 12:18:14 by memam            ###   ########.fr       */
=======
/*   Updated: 2022/09/23 15:45:27 by dpaulino         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
/*********** Includes **********/
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include <sys/stat.h>
# include <fcntl.h>
# include "get_next_line.h"
# include "structs.h"
# include <signal.h>
/*********** Colors **********/
# define BLACK_CLR "\e[39m"
# define RED_CLR "\e[41m"
# define GREEN_CLR "\e[32m"
# define YELLOW_CLR "\e[33m"
# define BLUE_CLR "\e[34m"
# define MAGENTA_CLR "\e[35m"
# define CYAN_CLR "\e[36m"
# define LIGHT_GRAY_CLR "\e[37m"
# define WHITE_CLR "\e[97m"
# define NORMAL_CLR "\e[21m"
# define BOLD "\e[1m"
# define RESET_ATT "\e[0m"
<<<<<<< HEAD


/*********** command **********/
int		ft_echo(t_command *command);
int		ft_pwd(void);
int		ft_env(char	**envp);
int		ft_exit(t_command *command);
int		ft_export(char **envp, char **args);
int		ft_unset(char **envp, char **args);
int     ft_wildcards(char *args);
/*********** env **********/
int		get_env_var_index(char **env, char *var);
int		env_var_count(char **envp);
int		set_env_var(char **envp, char *args);
int		is_valid_env_var(char *var);
char	**realloced_new_env(char **env, int index);
void	free_tab(char **tab);

=======

/*********** Commands **********/
int			ft_echo(t_command *command);
int			ft_pwd(void);
int			ft_env(char	**envp);
>>>>>>> main

/*********** Utils Functions**********/
void	    parse_phase_one(t_helper2 *buf_s, t_command **prompt, char *buffer, char **envp);
void		init_helper(t_helper *helper, t_command **prompt);
char		*get_last_meta(t_command *prompt, t_command *tmp);
void		init_envp_simple(t_helper *help, char **envp);
void		init_envp_complex(t_helper *help, char **envp);
void		struct_init_complex(t_command **prompt, char **envp);
int			find_char(char *buffer, char *c);
void		free_args(char **args);
void		free_prompt(t_command **prompt);
void		init_parse_struct(t_parse *p);
int			ft_array_size(char **array);
void		identify_dolar(t_command **prompt, char **args);
void		struct_init_simple(t_command **prompt, char **envp);
char		*get_single_path(char *cmd, char *env_path);
char		*buildin_path(char *cmd);
t_command	*get_last(t_command *prompt);
void		get_id(t_command **prompt);
void		f_and(t_command **prompt, t_command *tmp, char **envp, int **fd, int i);
void		close_pipes(t_command **prompt, int **fd);
/*********** Main Functions **********/
int			shell_prompt(char **argv, char **envp);
int			logo(char *path);
int			buffer_parsing(char *buffer, t_command **prompt, char **envp);
void		print_struct(t_command *prompt);
<<<<<<< HEAD
void		exec_simple(t_command *prompt, char **envp);
=======
int			exec_simple(t_command *prompt, char **envp);
>>>>>>> main
void		exec_complex(t_command **prompt, char **envp);
int			cd_cmd(t_command *prompt, char **envp);
void		get_commands(char **split, t_command **prompt, char **envp);
/*********** Parse Functions Utils **********/
void		identify_dolar(t_command **prompt, char **args);
void		get_dolar_char(t_command **prompt, char **arg, int i);
char		*get_dolar_var(char *tmp2, t_command **prompt);
void		parse_meta_chars(char *buffer, char **meta_chars, char **exe);
int			find_meta_char(char *buffer);
void		get_meta_chars(t_command **prompt, char **meta_chars);
int			parse_quotes(char **args, char *buffer);
/*********** Exec_Complex_Utils **********/
int			count_pipes(t_command **prompt);
<<<<<<< HEAD
void		free_fd(t_command **prompt, int **fd);
=======
void		free_fd(t_execc *exe, t_command **prompt);
>>>>>>> main
void		open_pipes(t_command **prompt, int **fd);
void		close_pipes(t_command **prompt, int **fd);
void		init_execc_struct(t_execc *exe, t_command **prompt);
/*********** Pipe Functions **********/
void		first_cmd(t_execc *exe, t_command **prompt, char **envp);
void		last_cmd(t_execc *exe, t_command **prompt, char **envp);
void		redirect_out(t_execc *exe, t_command **prompt, char **envp);
void		pipef(t_execc *exe, t_command **prompt, char **envp);
void		redirect_in(t_execc *exe, t_command **prompt, char **envp);
<<<<<<< HEAD
=======
void		alloc_fd(t_execc *exe, t_command **prompt);
void redirect_in_complex(t_execc *exe, t_command **prompt, char **envp);
>>>>>>> main
#endif