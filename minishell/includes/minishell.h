/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 13:25:13 by dpaulino          #+#    #+#             */
/*   Updated: 2022/09/23 00:09:33 by memam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
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
# include <stdbool.h>
//STRING COLORS
#define BLACK_CLR "\e[39m"
#define RED_CLR "\e[41m"
#define GREEN_CLR "\e[32m"
#define YELLOW_CLR "\e[33m"
#define BLUE_CLR "\e[34m"
#define MAGENTA_CLR "\e[35m"
#define CYAN_CLR "\e[36m"
#define LIGHT_GRAY_CLR "\e[37m"
#define WHITE_CLR "\e[97m"
#define NORMAL_CLR "\e[21m"
#define BOLD "\e[1m"
#define RESET_ATT "\e[0m"

/*********** command **********/
int		ft_echo(t_command *command);
int		ft_pwd(void);
int		ft_env(char	**envp);
int		ft_exit(char *args[]);
int		ft_export(char **envp, char **args);
int		ft_unset(char **envp, char **args);
/*********** env **********/
int		get_env_var_index(char **env, char *var);
int		set_env_var(char **envp, char *args);
bool	is_valid_env_var_idVar(char *var);
//char	**realloc_env_var(char **envp, int index);



//utils
void struct_init2(t_command **prompt, char **envp);
int	find_char(char *buffer, char c);
void free_args(char **args);
void	free_prompt(t_command **prompt);
void init_parse_struct(t_parse *p);
int	ft_array_size(char **array);
void identify_dolar(t_command **prompt, char **args);
void struct_init(t_command **prompt, char **envp);
char	*get_single_path(char *cmd, char *env_path);
char	*buildin_path(char *cmd);
t_command	*get_last(t_command *prompt);
//
int shell_prompt(char **argv, char **envp);
int logo(char *path);
int	parse_buffer(char *buffer, t_command **prompt, char **envp);
void    print_struct(t_command  *prompt);
void    exec_command(t_command *prompt, char **envp);
void exec_pipe_commands(t_command **prompt, char **envp);
int cd_cmd(t_command *prompt, char **envp);
#endif