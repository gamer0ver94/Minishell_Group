CC = gcc
CCFLAGS = -Wall -Wextra -Werror -g
LDFLAGS =  -lreadline -L/Users/${USER}/.brew/opt/readline/lib -I/Users/${USER}/.brew/opt/readline/include
LIBFT	=	-lft -L libft
LIBLINKS = -I./includes -I./libft/includes -I/Users/${USER}/.brew/opt/readline/include
APPNAME = minishell
EXT = .c
SRCDIR = srcs
OBJDIR = objs

SRC = $(wildcard $(SRCDIR)/*$(EXT))
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
	$(RM) $(DELOBJ) $(DEP) $(APPNAME)
	make fclean -C libft

fclean	:	clean

re		:	clean all
