# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vandre <vandre@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/28 15:31:24 by vandre            #+#    #+#              #
#    Updated: 2024/11/28 15:32:01 by vandre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = megaphone.cpp

CC = c++
NAME = megaphone

CFLAGS = -Wall -Wextra -Werror -std=c++98

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all