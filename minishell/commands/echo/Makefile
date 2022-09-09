CC = gcc
CCFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lft -L ../../libft
APPNAME = echo
EXT = .c
SRCDIR = srcs
OBJDIR = objs

SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
RM = rm
DELOBJ = $(OBJ)

all: $(APPNAME)

$(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o ../../builtin/$@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(CCFLAGS) -o $@ -c $<

clean:
	$(RM) $(DELOBJ) ../../builtin/$(APPNAME)

fclean: clean

.PHONY: clean

