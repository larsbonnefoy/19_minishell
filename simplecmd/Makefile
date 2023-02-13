###################################################################################################
##############################################PROGRAM##############################################
###################################################################################################
.SILENT:
###__MAIN PROGRAM__###

NAME = smpcmd

FILES = parse.c

SRCS = $(addprefix src/, $(FILES))

OBJ = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

FFLAGS = -fsanitize=address -g

RLINE = -lreadline
CC = @cc

RM = @rm -f

###__OS DETECTION__### no windows support for the moment

DETECTED_OS = $(shell uname)

###__LIBFT__##

LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

###__COMPILATION__###
$(NAME): $(OBJ)
		$(PRINT_OS)
		$(PRINT) "$(RED)making:	$(NOCOLOR)$(LIBFT_DIR)"
		@make --no-print-directory -C $(LIBFT_DIR)
		$(PRINT) "$(GREEN)done:\t$(NOCOLOR)$(LIBFT_DIR)"
		$(PRINT) "$(CYAN)making:\t$(NOCOLOR)$(NAME)"
		$(CC) $(CFLAGS)  $(OBJ) $(LIBFT) $(RLINE) -o $(NAME)
		$(PRINT) "$(GREEN)done:\t$(NOCOLOR)$(NAME)"

.c.o:
		$(CC) $(CLFAGS) -c $< -o $(<:.c=.o)

###__RULES__###
all: $(NAME)

clean:
		@make --no-print-directory clean -C $(LIBFT_DIR)
		$(RM) $(OBJ)

fclean: clean
		@make --no-print-directory fclean -C $(LIBFT_DIR)
		$(RM) $(NAME)

re :	fclean $(NAME)

.PHONY: all clean fclean re

###################################################################################################
############################################MISC###################################################
###################################################################################################

###__PRINT__###

PRINT = echo

# endif
PRINT_OS = echo "$(CYAN)OS:\t$(NOCOLOR)$(DETECTED_OS)"

###__COLORS__###
NOCOLOR = \033[0m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;32m
BLUE = \033[0;34m
CYAN = \033[0;36m
