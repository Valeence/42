# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vandre <vandre@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/26 17:04:59 by vandre            #+#    #+#              #
#    Updated: 2024/10/29 22:35:37 by vandre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR 			:=		Src
OBJ_DIR 			:=		Obj
LIBFT_DIR 			:=		Libs/libft
MLX_DIR				:= 		Libs/minilibx-linux

NAME 				= 		Cub3D

SRC					=		$(shell find $(SRC_DIR) -name "*.c")
OBJ 				=		$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

LIBFT				=		Libs/libft/libft.a
MLX					=		Libs/minilibx-linux/libmlx.a

CC					=		cc
CPPFLAGS			=		-I./include -I./libft/include -I./minilibx-linux -I/usr/include
MLXFLAGS			=		-lXext -lX11 -lmlx -L/usr/lib
CFLAGS				=		-Wall -Wextra -Werror -g3 -march=native

$(NAME):			$(OBJ) $(LIBFT) $(MLX)
					$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJ) -o $(NAME) $(LIBFT) -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

$(OBJ_DIR):
					mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
					@mkdir -p $(@D) $(OBJ_DIR)
					$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(LIBFT):
					make -C $(LIBFT_DIR)

$(MLX):
					make -C $(MLX_DIR)

all: 				$(NAME) $(LIBFT) $(MLX)

clean:		
			rm -rf $(OBJ_DIR)
			@make -C $(LIBFT_DIR) clean
			@make -C $(MLX_DIR) clean

fclean: 			clean
			rm -f $(NAME)
			@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
