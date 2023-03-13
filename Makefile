# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/23 10:34:10 by hdelmas           #+#    #+#              #
#    Updated: 2023/03/09 17:22:59 by hdelmas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FILES =  test_main.c 

SRC = $(addprefix src/, $(FILES))

SRCS = $(SRC) $(ALL)

OBJ = $(SRCS:.c=.o)

AR = ar -rcs

LDFLAGS = -L$(HOME)/.brew/opt/readline/lib

CPPFLAGS = -I$(HOME)/.brew/opt/readline/include

CFLAGS = -Wall -Wextra -Werror -IIncludes/ $(FFLAGS)

FFLAGS = -fsanitize=address -g

RLINE = -lreadline

CC = cc

RM = rm -f


###__LIBFT__###
LIBFT_DIR =	src/libft

LIBFT = $(LIBFT_DIR)/libft.a


###__EXP__###
EXP_NAME = expander.a

EXP_DIR = 	src/expander

EXP_SRC = 	$(EXP_DIR)/cleaner.c $(EXP_DIR)/expander.c $(EXP_DIR)/no_quote.c $(EXP_DIR)/lexer_to_expender.c\

EXP_OBJ = $(EXP_SRC:.c=.o)


###__ENV__###
ENV = env.a

ENV_DIR = 	src/env

ENV_SRC = 	$(addprefix $(ENV_DIR)/, $(ENV_FILE))

ENV_FILE =	ft_getenv.c env_list_manager.c env_to_list.c\
			env_reassign.c\

ENV_OBJ  = $(ENV_SRC:.c=.o)


###__LEXER__###
LEXER_NAME = lexer.a

LEXER_DIR = 	src/lexer

LEXER_FILE = 	lexer.c lexer_list_manager.c lexer_quotes.c lexer_quotes_utils.c\

LEXER_SRC = $(addprefix $(LEXER_DIR)/, $(LEXER_FILE))

LEXER_OBJ = $(LEXER_SRC:.c=.o)


###__PARSER__###
PARSER_NAME = parser.a

PARSER_DIR = 	src/parser

PARSER_FILE = 	simple_cmd.c

PARSER_SRC = $(addprefix $(PARSER_DIR)/, $(PARSER_FILE))

PARSER_OBJ = $(PARSER_SRC:.c=.o)


###__PROMPT__###
PROMPT_NAME = prompt.a

PROMPT_DIR = src/prompt

PROMPT_SRC = src/prompt/prompt.c

PROMPT_OBJ = $(PROMPT_SRC:.c=.o)

###__BUILTINS__###
BUILTINS_NAME = builtins.a

BUILTINS_DIR = ./src/builtins

BUILTINS_FILE =  ft_cd/ft_cd.c ft_echo/ft_echo.c ft_env/ft_env.c ft_exit/ft_exit.c ft_exit/exit_atol.c ft_export/ft_export.c ft_export/print_in_order.c ft_pwd/ft_pwd.c ft_unset/ft_unset.c\

BUILTINS_SRC = $(addprefix  $(BUILTINS_DIR)/, $(BUILTINS_FILE))

BUILTINS_OBJ = $(BUILTINS_SRC:.c=.o)

###__EXEC__###
EXEC_NAME = executor.a

EXEC_DIR = src/executor

EXEC_FILE = executor.c ft_execve.c in_redir.c out_redir.c error.c

EXEC_SRC = $(addprefix  $(EXEC_DIR)/, $(EXEC_FILE))

EXEC_OBJ = $(EXEC_SRC:.c=.o)

###__ALL__###
ALL = $(ENV_SRC) $(EXP_SRC) $(LEXER_SRC) $(PARSER_SRC) $(PROMPT_SRC) $(BUILTINS_SRC) $(EXEC_SRC)

ALL_NAME = $(ENV_NAME) $(EXP_NAME) $(LEXER_NAME) $(PARSER_NAME) $(PROMPT_NAME) $(BUILTINS_NAME) $(EXEC_NAME)




$(NAME): $(OBJ)
		make -C $(LIBFT_DIR)
		$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -g $(LDFLAGS) $(CPPFLAGS) $(RLINE)  -g -o $(NAME)

.c.o:
		$(CC) $(CLFAGS) $(CPPFLAGS) -c -g $< -g -o $(<:.c=.o)

all: $(NAME)
	

clean:
		make clean -C $(LIBFT_DIR)	
		$(RM) $(OBJ)

fclean: clean
		make fclean -C $(LIBFT_DIR)
		$(RM) $(NAME) $(ALL_NAME)

re :	fclean $(NAME)

env : $(ENV_OBJ)
		make -C $(LIBFT_DIR)
		$(AR) $(ENV_NAME) $(ENV_OBJ)

parser : $(PARSER_OBJ) $(LEXER_OBJ)
		make -C $(LIBFT_DIR)
		$(AR) $(PARSER_NAME) $(LEXER_OBJ) $(PARSER_OBJ)

lexer : $(LEXER_OBJ)
		make -C $(LIBFT_DIR)
		$(AR) $(LEXER_NAME) $(LEXER_OBJ)

expander : $(EXP_OBJ) $(ENV_OBJ)
		make -C $(LIBFT_DIR)
		$(AR) $(EXP_NAME) $(ENV_OBJ) $(EXP_OBJ)

prompt : $(PROMPT_OBJ) 
		make -C $(LIBFT_DIR)
		$(AR) $(PROMPT_NAME) $(PROMPT_OBJ)

.PHONY: all clean fclean re env lexer expander parser

# endif
