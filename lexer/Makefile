# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/12 12:01:38 by lbonnefo          #+#    #+#              #
#    Updated: 2023/02/17 11:25:38 by lbonnefo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lexer 

FILES = lexer.c \
		read_line.c \
		lexer_quotes.c \
		lexer_quotes_utils.c \
		lexer_list_manager.c \
		
SRCS= $(addprefix src/, $(FILES))

OBJ = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

$(NAME): $(OBJ)
				cc $(CFLAGS) $(OBJ) -o $(NAME) ../libft/libft.a -lreadline

.c.o:
		cc $(CFLAGS) -c $< -o $(<:.c=.o)

all: $(NAME) 

clean:
		rm -rf $(OBJ)

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
