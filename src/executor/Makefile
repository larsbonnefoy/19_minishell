# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/22 11:01:28 by lbonnefo          #+#    #+#              #
#    Updated: 2023/02/23 11:36:33 by lbonnefo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = executor 

FILES = executor.c ft_execve.c
		
SRCS= $(addprefix src/, $(FILES))

OBJ = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

$(NAME): $(OBJ)
				cc $(CFLAGS) $(OBJ) -o $(NAME) ../libft/libft.a

.c.o:
		cc $(CFLAGS) -c $< -o $(<:.c=.o)

all: $(NAME) 

clean:
		rm -rf $(OBJ)

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
