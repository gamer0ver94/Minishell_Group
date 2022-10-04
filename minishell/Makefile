CC = gcc
CCFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline
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
	$(CC) $(CCFLAGS) -o $@ $^ $(LDFLAGS) $(LIBFT)


$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(CCFLAGS) -o $@ -c $<

clean:
	$(RM) $(DELOBJ) $(DEP) $(APPNAME)
	make fclean -C libft

fclean	:	clean

re		:	clean all
