.SILENT:
###__MAIN PROGRAM__###

NAME = minishell

FILES = lexer_to_expender.c test_main.c 

SRCS = $(addprefix src/, $(FILES))

OBJ = $(FILES:.c=.o)

CFLAGS = -Wall -Wextra -Werror -Ilibft/ -Ienv/src/ -Iexpander/src/ $(FFLAGS)

FFLAGS = -fsanitize=address -g

RLINE = -lreadline

CC = @cc

AR = ar -rcs

RM = @rm -f

###__OS DETECTION__###

DETECTED_OS = $(shell uname)

###__LIBFT__##

LIBFT_DIR = ./libft

LIBFT = $(LIBFT_DIR)/libft.a

###__EXPANDER__###

EXP_DIR = ./expander

EXP = $(EXP_DIR)/expander.a

###__ENV__###

ENV_DIR = ./env

ENV = $(ENV_DIR)/env.a

###__LEXER__###

LEXER_DIR = ./lexer

LEXER = $(LEXER_DIR)/lexer.a

###__DEPENDENCIES__###

LIBFT_O = $(addprefix $(LIBFT_DIR)/, $(LIBFT_SRC))

LIBFT_SRC = ft_isascii.o ft_isalnum.o ft_isalpha.o ft_isdigit.o ft_isprint.o\
			ft_strlen.o ft_strlcpy.o ft_strlcat.o ft_strncmp.o ft_atoi.o\
			ft_strdup.o ft_strldup.o ft_tolower.o ft_toupper.o ft_strchr.o\
			ft_strrchr.o ft_strnstr.o ft_memset.o ft_bzero.o ft_memcpy.o\
			ft_memmove.o ft_memchr.o ft_memcmp.o ft_calloc.o ft_substr.o\
			ft_strjoin.o ft_strtrim.o ft_split.o ft_itoa.o ft_strmapi.o\
			ft_striteri.o ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o\
			ft_putnbr_fd.o ft_malloc.o ft_calloc_exit.o ft_strjoinf.o ft_strjoin_ff.o\

EXP_O = 	$(EXP_DIR)/src/cleaner.o $(EXP_DIR)/src/expander.o\

ENV_O = 	$(addprefix $(ENV_DIR)/src/, $(ENV_SRC))
ENV_SRC =	ft_getenv.o env_list_manager.o env_to_list.o env_to_list.o\
			env_reassign.o\

LEXER_SRC = lexer.o lexer_list_manager.o lexer_quotes.o lexer_quotes_utils.o\

LEXER_O = $(addprefix $(LEXER_DIR)/src/, $(LEXER_SRC))


LIBFT_O = $(LIBFT_DIR)/*.o
EXP_O = $(EXP_DIR)/src/*.o
ENV_O = $(ENV_DIR)/src/*.o

DEP = $(LIBFT_O) $(ENV_O) $(EXP_O) $(LEXER_O)

BIN = compiled_dependencies.a

###__COMPILATION__###
$(NAME): $(OBJ)
		$(PRINT_OS)
		@make --no-print-directory -C $(LIBFT_DIR)
		@make --no-print-directory -C $(ENV_DIR)
		@make --no-print-directory -C $(EXP_DIR)
		@make --no-print-directory -C $(LEXER_DIR)
		$(PRINT) "$(YELLOW)linking $(NOCOLOR)libraries\t"
		$(AR) $(BIN) $(DEP)
		$(PRINT) "$(GREEN)done\t$(NOCOLOR)"
		$(PRINT) "$(CYAN)making:\t$(NOCOLOR)$(NAME)"
		$(CC) $(CFLAGS) $(OBJ) -g $(BIN) -g $(RLINE) -g -o $(NAME)
		$(PRINT) "$(GREEN)done:\t$(NOCOLOR)$(NAME)"

.c.o:
		$(CC) $(CLFAGS) -c -g $< -g -o $(<:.c=.o)

###__RULES__###
all: $(NAME)

clean:
		$(PRINT) "$(BLUE)cleaning\t$(NOCOLOR)"
		@make --no-print-directory clean -C $(LIBFT_DIR)
		@make --no-print-directory clean -C $(EXP_DIR)
		@make --no-print-directory clean -C $(LEXER_DIR)
		@make --no-print-directory clean -C $(ENV_DIR)
		$(RM) $(BIN)
		$(RM) $(OBJ)

fclean: clean
		$(PRINT) "$(BLUE)all\t$(NOCOLOR)"
		@make --no-print-directory fclean -C $(LIBFT_DIR)
		@make --no-print-directory fclean -C $(EXP_DIR)
		@make --no-print-directory fclean -C $(LEXER_DIR)
		@make --no-print-directory fclean -C $(ENV_DIR)
		$(RM) $(NAME)

re :	fclean $(NAME)

# sanitize : all
# 		VAR = 1

.PHONY: all clean fclean re 

###__PRINT__###

PRINT = echo

# endif
PRINT_OS = echo "$(CYAN)OS:\t$(NOCOLOR)$(DETECTED_OS)"

###__COLORS__###
NOCOLOR = \033[0m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
CYAN = \033[0;36m
