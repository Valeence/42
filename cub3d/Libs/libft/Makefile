# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vandre <vandre@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/15 14:01:04 by zachamou          #+#    #+#              #
#    Updated: 2024/10/26 17:23:33 by vandre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -g3

SRCS = $(wildcard *.c)

OBJS = ${SRCS:.c=.o}

NAME = libft.a

%.o : %.c
	gcc ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	ar rc ${NAME} ${OBJS}

all : ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}
	rm -f a.out

re: fclean all clean 

.PHONY:	fclean	all