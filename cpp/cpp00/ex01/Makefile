# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vandre <vandre@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/28 15:43:44 by vandre            #+#    #+#              #
#    Updated: 2024/12/01 19:07:10 by vandre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = \
		Main.cpp\
		Contact.cpp\
		PhoneBook.cpp\

CC = c++
NAME = Phone

CFLAGS = -Wall -Wextra -Werror -std=c++98 -g3

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