.SILENT:
###__MAIN PROGRAM__###

NAME = smpcmd

FILES = test_main.c

SRCS = $(addprefix src/, $(FILES))

OBJ = $(FILES:.c=.o)

CFLAGS = -Wall -Wextra -Werror -Ilibft/ -Ilocal_env/src/ -Isimplecmd/src/ $(FFLAGS)

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

###__CLEANER_N_EXPAND__###

CLNR_DIR = ./simplecmd

CLNR = $(CLNR_DIR)/clean_n_expand.a

###__LOCAL__###

LOCAL_DIR = ./local_env

LOCAL = $(LOCAL_DIR)/local.a

###__DEPENDENCIES__###

LIBFTO = $(LIBFT_DIR)/*.o
CLNRO = $(CLNR_DIR)/src/*.o
LOCALO = $(LOCAL_DIR)/src/*.o

DEP = $(LIBFTO) $(LOCALO) $(CLNRO)

BIN = compiled_dependencies.a

###__COMPILATION__###
$(NAME): $(OBJ)
		$(PRINT_OS)
		@make --no-print-directory -C $(LIBFT_DIR)
		@make --no-print-directory -C $(LOCAL_DIR)
		@make --no-print-directory -C $(CLNR_DIR)
		$(PRINT) "$(YELLOW)linking $(NOCOLOR)libraries\t"
		$(AR) $(BIN) $(DEP)
		$(PRINT) "$(GREEN)done\t$(NOCOLOR)"
		$(PRINT) "$(CYAN)making:\t$(NOCOLOR)$(NAME)"
		$(CC) $(CFLAGS) $(OBJ) -g $(BIN) -g $(RLINE) -g -o $(NAME)
		$(PRINT) "$(GREEN)done:\t$(NOCOLOR)$(NAME)"

.c.o:
		$(CC) $(CLFAGS) -c $< -o $(<:.c=.o)

###__RULES__###
all: $(NAME)

clean:
		$(PRINT) "$(BLUE)cleaning\t$(NOCOLOR)"
		@make --no-print-directory clean -C $(LIBFT_DIR)
		@make --no-print-directory clean -C $(CLNR_DIR)
		@make --no-print-directory clean -C $(LOCAL_DIR)
		$(RM) $(BIN)
		$(RM) $(OBJ)

fclean: clean
		$(PRINT) "$(BLUE)all\t$(NOCOLOR)"
		@make --no-print-directory fclean -C $(LIBFT_DIR)
		@make --no-print-directory fclean -C $(CLNR_DIR)
		@make --no-print-directory fclean -C $(LOCAL_DIR)
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
