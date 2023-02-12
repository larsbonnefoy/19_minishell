# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/12 12:01:38 by lbonnefo          #+#    #+#              #
#    Updated: 2023/02/12 12:15:41 by lbonnefo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lexer 

FILES = lexer.c \
		read_line.c \
		
SRCS= $(addprefix src/, $(FILES))

OBJ = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

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
