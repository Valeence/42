# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vandre <vandre@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/24 17:22:28 by vandre            #+#    #+#              #
#    Updated: 2024/02/01 03:26:13 by vandre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR		:=		src
OBJ_DIR		:=		obj
LIBFT_DIR	:=		libft

INCLUDE		=		include/push_swap.h
LIBFT		=		libft/libft.a

NAME		=		push_swap
SRC			=		$(wildcard $(SRC_DIR)/*.c)
OBJ			=		$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)	

FLAGS		=		-Wall -Werror -Wextra -g3
CC			=		cc

$(NAME):			$(OBJ) $(LIBFT)
					$(CC) -o $(NAME) $(OBJ) $(LIBFT) $(FLAGS)

$(OBJ_DIR):
					mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(LIBFT):
					make -C $(LIBFT_DIR)

all:				$(NAME) $(LIBFT)

clean:
					rm -rf $(OBJ_DIR)
					@make -C $(LIBFT_DIR) clean

fclean:				clean
					rm -f $(NAME)
					@make -C $(LIBFT_DIR) fclean

re:					fclean all

.PHONY:				all clean fclean re
