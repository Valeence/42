# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vandre <vandre@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/02 11:04:25 by vandre            #+#    #+#              #
#    Updated: 2024/09/02 11:04:27 by vandre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom de l'exécutable
NAME		:=		my_program

# Compilateur et options
CC			:=		c++
FLAGS		:=		-Wall -Werror -Wextra -std=c++98

# Fichiers sources et objets
SRC			:=		main.cpp
OBJ			:=		$(SRC:.cpp=.o)

# Règle principale
all:		$(NAME)

# Règle pour créer l'exécutable
$(NAME):	$(OBJ)
			$(CC) $(FLAGS) -o $(NAME) $(OBJ)

# Règle pour créer les fichiers objets
%.o:		%.cpp
			$(CC) $(FLAGS) -c $< -o $@

# Nettoyage des fichiers objets
clean:
			rm -f $(OBJ)

# Nettoyage complet
fclean:		clean
			rm -f $(NAME)

# Recompiler tout
re:			fclean all

# Pour éviter que make traite ces noms de règles comme des fichiers
.PHONY:		all clean fclean re