/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 13:25:13 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/20 22:10:28 by dpaulino         ###   ########.fr       */
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
# include <sys/ioctl.h>
# include <signal.h>
# include <termios.h>
# include <sys/types.h> //opendir, readdir, closedir
# include <dirent.h> //opendir, readdir, closedir
/*********** Colors **********/
# define BLACK_CLR "\e[39m"
# define RED_CLR "\001\033[1;91m\002"
# define GREEN_CLR "\001\033[1;92m\002"
# define YELLOW_CLR "\001\033[1;93m\002"
# define BLUE_CLR "\001\033[1;94m\002"
# define MAGENTA_CLR "\001\033[1;95m\002"
# define CYAN_CLR "\e[36m"
# define LIGHT_GRAY_CLR "\e[37m"
# define WHITE_CLR "\001\033[0;97m\002"
# define NORMAL_CLR "\001\033[0;39m\002"
# define BOLD "\e[1m"
# define RESET_ATT "\e[0m"

/*********** Commands **********/
int			ft_echo(t_command *command);
int			ft_pwd(void);
int			t_env(char	**envp);
int			ft_exit(t_command *command, char **envp);
int			ft_export(char **envp, char **args);
int			ft_unset(char **envp, char **args);
void		t_signals(void);
int			builtin(t_command *prompt, char **envp);
int			builtin_env(t_command *prompt, char **envp);
/*********** Bonus **********/
// int		    ft_wildcards(char *args);

/*********** Utils Functions**********/
extern int	g_status;
void		parse_phase_one(t_helper2 *buf_s, t_command **prompt, \
char *buffer, char **envp);
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
void		close_pipes(t_command **prompt, int **fd);
/*********** Main Functions **********/
void		shell_prompt(char **envp);
int			logo(char *path);
int			buffer_parsing(char *buffer, t_command **prompt, char **envp);
void		print_struct(t_command *prompt);
int			exec_simple(t_command *prompt, char **envp);
void		exec_complex(t_command **prompt, char **envp);
int			cd_cmd(t_command *prompt, char **envp);
void		get_commands(char **split, t_command **prompt, char **envp);
/*********** Parse Functions Utils **********/
void		identify_dolar(t_command **prompt, char **args);
void		get_dolar_char(t_command **prompt, char **arg, int i);
char		*get_dolar_var(char *tmp2, t_command **prompt);
void		parse_meta_chars(char *buffer, t_helper2 *buf_s);
int			find_meta_char(char *buffer);
void		get_meta_chars(t_command **prompt, t_helper2 *buf_s);
int			parse_quotes(char **args, char *buffer);
/*********** Exec_Complex_Utils **********/
int			count_pipes(t_command **prompt);
void		free_fd(t_execc *exe, t_command **prompt);
void		open_pipes(t_command **prompt, int **fd);
void		init_execc_struct(t_execc *exe, t_command **prompt);
/*********** Pipe Functions **********/
void		redirect_out(t_execc *exe, t_command **prompt, char **envp);
void		pipef(t_execc *exe, t_command **prompt, char **envp);
void		redirect_in(t_execc *exe, t_command **prompt, char **envp);
void		alloc_fd(t_execc *exe, t_command **prompt);
void		redirect_in_complex(t_execc *exe, t_command **prompt, char **envp);
int			set_env_var(char **envp, char *args);
char		**realloced_new_env(char **env, int index);
int			get_env_var_index(char **env, char *var);
void		free_tab(char **tab);
void		last_cmd(t_execc *exe, t_command **prompt, char **envp);
void		close_files(t_command **prompt, int **file);
void		alloc_files(t_execc *exe, t_command **prompt);
void		open_files(t_command **prompt, int **file);
void		free_matrix(char **matrix);
int			ft_env(char	**envp);
/*********** Envp Generator **********/
void		free_envp(char **envp);
void		create_env(char **new_envp, char **envp);
/*********** Norminette helper functions **********/
void		double_quotes(t_parse *p, char **args, char *buffer);
void		jump_spaces(t_parse *p, char **args, char *buffer);
int			parse_without_meta(t_helper2 *b, char *buf, t_command **pt, \
char **env);
int			count_files(t_command **prompt);
void		free_files(t_execc *exe, t_command **prompt);
/*********** New export **********/
int			var_exist(char *arg, char **envp);
int			replace_var(char *parse, char *arg, char **envp);
int			delete_var(char **envp, int j);
int			is_valid_env_var(char *var);
void		fork_redir_in_simple(t_execc *exe, t_command **prompt, char **envp);
void		fork_redir_in_complex(t_execc *exe, t_command **prompt, \
char **envp, int	*file);
int			redir_prompt(t_execc *exe, int *file);
void		exit_ctl_d(char *buffer, char **envp);
void		exit_prompt(char**envp);
int			check_path(char **envp);
void		verify_access(t_command *prompt);
void		free_helper(t_command *tmp, t_command *aux, int i);
void		ft_close_exit(int *file, t_command **prompt, char **envp, \
t_execc *exe);
void		ft_close_exit_complex(t_command **prompt, t_execc *exe, int *file, \
char **envp);
void		export_list(char **envp);
void		sighandler(int signal);
int	termios_config(struct termios *t_config);

#endif