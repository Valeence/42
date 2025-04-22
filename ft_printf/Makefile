# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vandre <vandre@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/18 15:55:38 by vandre            #+#    #+#              #
#    Updated: 2023/11/18 16:57:52 by vandre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	ft_printf.c\
					ft_printf_utils.c\
					ft_strchr.c\
					ft_strlen.c\

OBJS		= ${SRCS:.c=.o}
NAME		= libftprintf.a
CC			= cc -Wall -Wextra -Werror

all: ${NAME}

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c ft_printf.h
	$(CC) -I. -c $< -o $@

bonus: ${OBJS_BONUS} ft_printf.h
	ar rcs ${NAME} ${OBJS_BONUS}

clean:
	rm -f ${OBJS}

fclean:		clean
	rm -f ${NAME} ${OBJS_BONUS}

re:			fclean all

.PHONY:		all clean fclean re