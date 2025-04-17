/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:00:00 by user42            #+#    #+#             */
/*   Updated: 2025/04/17 10:59:30 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

# define IMG_SIZE 32

# ifdef __linux__
// Keycodes Linux (X11 / minilibx-linux)
#  define ESC_KEY 65307
#  define W_KEY 119
#  define A_KEY 97
#  define S_KEY 115
#  define D_KEY 100
#  define U_ARROW 65362  // Up
#  define L_ARROW 65361  // Left
#  define D_ARROW 65364  // Down
#  define R_ARROW 65363  // Right

# elif defined(__APPLE__)
// Keycodes macOS (minilibx-opengl or minilibx-macos)
#  define ESC_KEY 53
#  define W_KEY 13
#  define A_KEY 0
#  define S_KEY 1
#  define D_KEY 2
#  define U_ARROW 126
#  define L_ARROW 123
#  define D_ARROW 125
#  define R_ARROW 124

# else
#  error "Unsupported platform"
# endif

typedef struct s_img
{
	void	*img;
	size_t	width;
	size_t	height;
}	t_img;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	int		player_count;
	int		exit_count;
	int		collectibles;
	int		collected;
	int		moves;
	int		exit_x;
	int		exit_y;
	t_img	wall;
	t_img	player;
	t_img	collectible;
	t_img	exit;
	t_img	floor;
}	t_game;

// events.c
int		key_press(int keycode, t_game *game);
int		close_game(t_game *game);

// free.c
void	exit_error(char *message);
void	free_copy(char **copy, int height);
void	free_map(t_game *game);
void	free_game(t_game *game);

// init_img.c
int		init_images(t_game *game);

// init.c
void	init_game(t_game *game);
int		init_window(t_game *game);
void	setup_hooks(t_game *game);

// main.c
void	print_stats(t_game *game);
int		main(int argc, char **argv);

// map_reader.c
int		read_map(char *filename, t_game *game);

// map_validator.c
int		validate_map(t_game *game);

//path_finder.c
int		check_path(t_game *game);
char	**copy_map(t_game *game);

// player.c
int		move_player(t_game *game, int new_x, int new_y);

// render.c
void render_game(t_game *game);
void render_full_game(t_game *game);
void render_tile(t_game *game, t_img *img, int x, int y); 

#endif