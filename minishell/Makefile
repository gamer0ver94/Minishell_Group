CC = gcc
CCFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline -g
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
	make -C commands/echo
	make -C commands/env
	make -C commands/exit
	make -C commands/pwd
	$(CC) $(CCFLAGS) -o $@ $^ $(LDFLAGS) $(LIBFT)

$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(CCFLAGS) -o $@ -c $<

clean:
	make fclean -C libft
	make fclean -C commands/echo
	make fclean -C commands/env
	make fclean -C commands/exit
	make fclean -C commands/pwd
	$(RM) $(DELOBJ) $(DEP) $(APPNAME)

fclean	:	clean

re		:	clean all