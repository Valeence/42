# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vandre <vandre@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/21 13:10:51 by vandre            #+#    #+#              #
#    Updated: 2024/01/18 11:39:20 by vandre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR 			:=		src
OBJ_DIR 			:=		obj
LIBFT_DIR 			=		libft
MLX_DIR				= 		minilibx-linux


NAME 				= 		so_long

SRC					=		$(wildcard $(SRC_DIR)/*.c)
OBJ 				=		$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIBFT				=		libft/libft.a
MLX					=		minilibx-linux/libmlx.a

CC					=		cc
CPPFLAGS			=		-I./include -I./libft/include -I./minilibx-linux -I/usr/include
MLXFLAGS			=		-lXext -lX11 -lmlx -L/usr/lib
CFLAGS				=		-Wall -Wextra -Werror -g3

$(NAME):			$(OBJ) $(LIBFT) $(MLX)
						$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJ) -o $(NAME) $(LIBFT) -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

$(OBJ_DIR):
					mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
							@mkdir -p $(@D)
							$(CC) $(CPPFLAGS) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(LIBFT):
					make -C $(LIBFT_DIR)

$(MLX):
					make -C $(MLX_DIR)

all: 						$(NAME) $(LIBFT) $(MLX)

clean:		
			rm -rf $(OBJ_DIR)
			@make -C $(LIBFT_DIR) clean
			@make -C $(MLX_DIR) clean

fclean: 			clean
			rm -f $(NAME)
			@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
