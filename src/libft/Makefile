# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/07 08:14:24 by hdelmas           #+#    #+#              #
#    Updated: 2023/03/20 10:45:25 by lbonnefo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
 
SRCS = 	ft_isascii.c ft_isalnum.c ft_isalpha.c ft_isdigit.c ft_isprint.c\
		ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strncmp.c ft_atoi.c\
		ft_strdup.c ft_strldup.c ft_tolower.c ft_toupper.c ft_strchr.c\
		ft_strrchr.c ft_strnstr.c ft_memset.c ft_bzero.c ft_memcpy.c\
		ft_memmove.c ft_memchr.c ft_memcmp.c ft_calloc.c ft_substr.c\
		ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c\
		ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c\
		ft_putnbr_fd.c ft_malloc.c ft_calloc_exit.c ft_strjoinf.c ft_strjoin_ff.c\
		ft_realloc_tab.c ft_tabdup.c\
		

OBJ = $(SRCS:.c=.o)

BONUSOBJ = $(BONUS:.c=.o)

AR = ar -rcs

CFLAGS = -Wall -Wextra -Werror #$(FFLAGS)

FFLAGS = -fsanitize=address -g

CC = cc

RM = rm -f

$(NAME): $(OBJ)
		$(AR) $(NAME) $(OBJ)
.c.o:
		$(CC) $(CFLAGS) -g -c $< -g -o $(<:.c=.o)

all: $(NAME)

clean:
		$(RM) $(OBJ) $(BONUSOBJ)

fclean: clean 
		$(RM) $(NAME)

re :	fclean all

.PHONY: all clean fclean re

