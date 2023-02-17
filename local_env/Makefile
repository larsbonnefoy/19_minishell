.SILENT:
###__MAIN PROGRAM__###

NAME = local.a

FILES = ft_get_local_env.c local_env_list_manager.c\

SRCS = $(addprefix src/, $(FILES))

OBJ = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror $(FFLAGS)

FFLAGS = -fsanitize=address -g

CC = @cc

AR = ar -rcs

RM = @rm -f

###__LIBFT__##

LIBFT_DIR = ../libft

LIBFT = $(LIBFT_DIR)/libft.a

###__LOCAL__###

LOCAL_DIR = ../local_env

LOCAL = $(LOCAL_DIR)/local.a

###__LIB__###

LIB = $(LIBFT) $(LOCAL) 

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
