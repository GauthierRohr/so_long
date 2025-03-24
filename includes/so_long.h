/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 01:58:23 by grohr             #+#    #+#             */
/*   Updated: 2025/03/16 16:31:44 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include <unistd.h> //For usleep
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include </opt/homebrew/include/SDL2/SDL.h>
# include </opt/homebrew/include/SDL2/SDL_mixer.h>

# define WIDTH 1200
# define HEIGHT 1000

typedef struct s_enemy
{
    int x;
    int y;
    int direction; // 0 = horizontal, 1 = vertical
    int move_counter; // Pour contrôler la vitesse de mouvement
} t_enemy;

// Modification de la structure t_game pour ajouter les ennemis
typedef struct s_game
{
    void    *mlx;
    void    *win;
    char    **map;
    int     player_x;
    int     player_y;
    int     collectibles;
    int     collected;
    void    *wall_img;
    void    *dalle_img;
    void    *player_img;
    void    *item_img;
    void    *exit_img;
    void    *enemy_img; // Nouvelle image pour l'ennemi
    int     img_width;
    int     img_height;
    Mix_Music *music;
    bool    keys[128];
    int     move_count;
    t_enemy *enemies; // Tableau d'ennemis
    int     enemy_count; // Nombre d'ennemis
    bool    game_over; // Pour indiquer si le joueur a perdu
} t_game;

typedef struct s_valid_path
{
    int collectibles_found;
    int exit_found;
} t_valid_path;

char    **parse_map(char *file, t_game *game);
void    load_textures(t_game *game);
void    render_map(t_game *game);
int     handle_key(int key, t_game *game);
int     close_window(t_game *game);
void    update_player_position(t_game *game);
size_t  get_map_height(char **map);

// Enemy
void    init_enemies(t_game *game);
void    move_enemies(t_game *game);
void    check_enemy_collision(t_game *game);
int loop_hook(t_game *game);

// Map validation
int     rectangular_map(char **map);
int     wall_contour(char **map);
int     valid_path(t_game *game, char **map_copy);
void    free_map(char **map);
char    **copy_map(char **map);

// Audio
void    init_audio(t_game *game);
void    cleanup_audio(t_game *game);

#endif