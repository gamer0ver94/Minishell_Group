CC = gcc
CCFLAGS = -Wall -Wextra -Werror -g
LDFLAGS =  -lreadline -L/Users/${USER}/.brew/opt/readline/lib -I/Users/${USER}/.brew/opt/readline/include
LIBFT	=	-lft -L libft
LIBLINKS = -I./includes -I./libft/includes -I/Users/${USER}/.brew/opt/readline/include
APPNAME = minishell
EXT = .c
SRCDIR = srcs
OBJDIR = objs
SRC =  srcs/main.c \
				srcs/buffer_parsing.c \
				srcs/buffer_parsing_utils.c \
				srcs/cd_cmd.c \
				srcs/cmd_error.c \
				srcs/envp_gener.c \
				srcs/exe_complex_utils.c \
				srcs/exe_complex_utils2.c \
				srcs/exec_builtin.c \
				srcs/exec_complex.c \
				srcs/exec_simple.c \
				srcs/exec_simple_verify.c \
				srcs/exit_ctl_d.c \
				srcs/free_matrix.c \
				srcs/ft_echo.c \
				srcs/ft_env.c \
				srcs/ft_exit.c \
				srcs/ft_export.c \
				srcs/ft_pipe.c \
				srcs/ft_pwd.c \
				srcs/ft_redir_in.c \
				srcs/ft_redir_in_utils.c\
				srcs/ft_redir_in_utils2.c \
				srcs/ft_redir_out.c \
				srcs/ft_unset.c \
				srcs/get_next_line.c \
				srcs/get_next_line_utils.c \
				srcs/logo.c \
				srcs/parse_dolar.c \
				srcs/parse_dolar_utils.c \
				srcs/parse_meta_char.c \
				srcs/parsing_utils.c \
				srcs/parsing_utils2.c \
				srcs/print_struct.c \
				srcs/shell_prompt.c \
				srcs/struct_init.c \
				srcs/struct_init_free.c \
				srcs/struct_init_utils.c \
				srcs/ft_signal.c \

OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
RM = rm -rf
DELOBJ = $(OBJ)

all: $(APPNAME)

$(APPNAME): $(OBJ)
	make -C libft
	$(CC) $(CCFLAGS) -o $@ $^ $(LDFLAGS) $(LIBFT)


$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) -g3 $(CCFLAGS) ${LIBLINKS} -o $@ -c $<

clean:
	$(RM) $(DELOBJ) 
	make clean -C libft

fclean	:	clean
		$(RM) $(APPNAME)
		make fclean -C libft

re		:	clean all