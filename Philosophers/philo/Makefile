# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vandre <vandre@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/23 02:33:43 by vandre            #+#    #+#              #
#    Updated: 2024/03/13 19:59:42 by vandre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 				= 		philo

SRC					=		$(wildcard *.c)
OBJ					=		$(SRC:.c=.o)

CC					=		cc -Wall -Wextra -Werror -g3 -pthread #-fsanitize=thread

$(NAME)	:	$(OBJ)
		$(CC) -o $(NAME) $(OBJ)

all		:	$(NAME)

clean	:
		rm -rf $(OBJ)

fclean	:	clean
		rm -f $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re