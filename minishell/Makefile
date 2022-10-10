CC = gcc
CCFLAGS = -Wall -Wextra -Werror
LINKS = -lreadline -L${HOME}/goinfre/.brew/opt/readline/lib
LIBLINKS = -I./includes -I./libft/includes -I ${HOME}/goinfre/.brew/opt/readline/include
LIBFT	=	-lft -L libft
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
	$(CC) $(CCFLAGS) -o $@ $^ $(LINKS) $(LIBFT)


$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(CCFLAGS) $(LIBLINKS) -o $@ -c $<

clean:
	$(RM) $(DELOBJ) $(DEP) $(APPNAME)
	make fclean -C libft

fclean	:	clean

re		:	clean all
