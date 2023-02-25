# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/23 10:34:10 by hdelmas           #+#    #+#              #
#    Updated: 2023/02/25 15:14:57 by hdelmas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:
NAME = minishell

FILES = lexer_to_expender.c test_main.c 

SRC = $(addprefix src/, $(FILES))

SRCS = $(SRC) $(ALL)

OBJ = $(SRCS:.c=.o)

AR = ar -rcs

CFLAGS = -Wall -Wextra -Werror -Isrc/ $(FFLAGS)

FFLAGS = -fsanitize=address -g

RLINE = -lreadline

CC = cc

RM = rm -f


###__LIBFT__###
LIBFT_DIR =	./libft

LIBFT = $(LIBFT_DIR)/libft.a


###__EXP__###
EXP_NAME = expander.a

EXP_DIR = 	./expander

EXP_SRC = 	$(EXP_DIR)/src/cleaner.c $(EXP_DIR)/src/expander.c\

EXP_OBJ = $(EXP_SRC:.c=.o)


###__ENV__###
ENV = env.a

ENV_DIR = 	./env

ENV_SRC = 	$(addprefix $(ENV_DIR)/src/, $(ENV_FILE))

ENV_FILE =	ft_getenv.c env_list_manager.c env_to_list.c\
			env_reassign.c\

ENV_OBJ  = $(ENV_SRC:.c=.o)


###__LEXER__###
LEXER_NAME = lexer.a

LEXER_DIR = 	./lexer

LEXER_FILE = 	lexer.c lexer_list_manager.c lexer_quotes.c lexer_quotes_utils.c\

LEXER_SRC = $(addprefix $(LEXER_DIR)/src/, $(LEXER_FILE))

LEXER_OBJ = $(LEXER_SRC:.c=.o)


###__PARSER__###
PARSER_NAME = parser.a

PARSER_DIR = 	./parser

PARSER_FILE = 	simple_cmd.c

PARSER_SRC = $(addprefix $(PARSER_DIR)/src/, $(PARSER_FILE))

PARSER_OBJ = $(PARSER_SRC:.c=.o)


###__PROMPT__###
PROMPT_NAME = prompt.a

PROMPT_DIR = ./prompt

PROMPT_SRC = ./prompt/prompt.c

PROMPT_OBJ = $(PROMPT_SRC:.c=.o)


###__ALL__###
ALL = $(ENV_SRC) $(EXP_SRC) $(LEXER_SRC) $(PARSER_SRC) $(PROMPT_SRC)

ALL_NAME = $(ENV_NAME) $(EXP_NAME) $(LEXER_NAME) $(PARSER_NAME) $(PROMPT_NAME)



$(NAME): $(OBJ)
		@make --no-print-directory -C $(LIBFT_DIR)
		$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -g $(RLINE) -g -o $(NAME)

.c.o:
		$(CC) $(CLFAGS) -c -g $< -g -o $(<:.c=.o)

all: $(NAME)
	

clean:
		@make --no-print-directory clean -C $(LIBFT_DIR)	
		$(RM) $(OBJ)

fclean: clean
		@make --no-print-directory fclean -C $(LIBFT_DIR)
		$(RM) $(NAME) $(ALL_NAME)

re :	fclean $(NAME)

env : $(ENV_OBJ)
		@make --no-print-directory -C $(LIBFT_DIR)
		$(AR) $(ENV_NAME) $(ENV_OBJ)

parser : $(PARSER_OBJ) $(LEXER_OBJ)
		@make --no-print-directory -C $(LIBFT_DIR)
		$(AR) $(PARSER_NAME) $(LEXER_OBJ) $(PARSER_OBJ)

lexer : $(LEXER_OBJ)
		@make --no-print-directory -C $(LIBFT_DIR)
		$(AR) $(LEXER_NAME) $(LEXER_OBJ)

expander : $(EXP_OBJ) $(ENV_OBJ)
		@make --no-print-directory -C $(LIBFT_DIR)
		$(AR) $(EXP_NAME) $(ENV_OBJ) $(EXP_OBJ)

prompt : $(PROMPT_OBJ) 
		@make --no-print-directory -C $(LIBFT_DIR)
		$(AR) $(PROMPT_NAME) $(PROMPT_OBJ)

.PHONY: all clean fclean re env lexer expander parser

# endif
