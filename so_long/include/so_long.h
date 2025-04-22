/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vandre <vandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 21:37:34 by vandre            #+#    #+#             */
/*   Updated: 2024/01/18 12:01:35 by vandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../minilibx-linux/mlx.h"
# include "../libft/include/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

# define KEY_W		119
# define KEY_A		97
# define KEY_S		115
# define KEY_D		100
# define KEY_ESC	65307

typedef struct s_img
{
	void	*floor;
	void	*wall;
	void	*coin;
	void	*exit;
	void	*player;
}				t_img;

typedef struct s_game
{
	char	**map;
	char	**mlx_map;
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	int		free_height;
	int		is_coin;
	int		is_exit;
	int		is_player;
	int		pos_x;
	int		pos_y;
	int		exit_x;
	int		exit_y;
	int		check_coin;
	int		check_exit;
	int		move;
	t_img	img;
}				t_game;

int		check_arg(char *str);
void	check_size(t_game *game, char *map_path);
void	fill_map(t_game *game, char *map_path);
int		ft_strlen_sl(char *str);
void	check_map(t_game *game);
void	check_top_bottom(t_game *game);
void	check_chars(t_game *game);
void	check_square(t_game *game);
void	check_boundy(t_game *game);
void	check_player(t_game *game);
void	check_exit(t_game *game);
void	check_coins(t_game *game);
void	check_path(t_game *game);
int		flood_fill(t_game *game, int x, int y);
void	init_mlx(t_game *game);
void	print_mlx(t_game *game);
void	print_map(t_game *game, char c, int x, int y);
int		key_hook(int keycode, t_game *game);
void	print_img(t_game *game, char c, int x, int y);
void	close_game(t_game *game);
int		close_window(t_game *game);
void	game_print_right(t_game *game);
void	game_print_left(t_game *game);
void	game_print_up(t_game *game);
void	game_print_down(t_game *game);
void	free_map(t_game *game);

#endif