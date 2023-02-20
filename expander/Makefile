.SILENT:

###__MAIN PROGRAM__###

NAME = expander.a

FILES = cleaner.c expander.c\

SRCS = $(addprefix src/, $(FILES))

OBJ = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror $(FFLAGS)  

FFLAGS = -fsanitize=address -g

CC = @cc

AR = ar -rcs

RM = @rm -f

###__COMPILATION__###
$(NAME): $(OBJ)
		$(PRINT) "$(RED)making:\t$(NOCOLOR)$(NAME)"
		$(AR) $(NAME) $(OBJ)
		$(PRINT) "$(GREEN)done:\t$(NOCOLOR)$(NAME)"

.c.o:
		$(CC) $(CFLAGS) -g -c $< -g -o $(<:.c=.o)

###__RULES__###
all: $(NAME)

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re :	fclean $(NAME)

.PHONY: all clean fclean re 

###__PRINT__###

PRINT = echo

###__COLORS__###
NOCOLOR = \033[0m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;32m
BLUE = \033[0;34m
CYAN = \033[0;36m
