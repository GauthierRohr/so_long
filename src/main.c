/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:34:53 by grohr             #+#    #+#             */
/*   Updated: 2025/03/16 16:29:08 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int close_window(t_game *game)
{
    cleanup_audio(game);  // Nettoyer l'audio avant de quitter
    
    // Libérer la mémoire des ennemis
    if (game->enemies)
        free(game->enemies);
    
    if (game->mlx)
    {
        if (game->win)
            mlx_destroy_window(game->mlx, game->win);
        // Only call mlx_destroy_display on Linux
        #ifdef __linux__
            mlx_destroy_display(game->mlx);
        #endif
        free(game->mlx);
    }
    exit(0);
}

int main(int ac, char **av)
{
    if (ac < 2)
        return (1);
    t_game game;

    game.mlx = mlx_init();
    game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "So Long");
    game.map = parse_map(av[1], &game);
    if (!game.map)
        return (1);
    game.collected = 0;
    game.music = NULL;
    game.move_count = 0; // Initialiser le compteur de mouvements
    game.enemies = NULL;
    game.game_over = false;

    init_audio(&game);
    load_textures(&game); // Load textures
    init_enemies(&game);  // Initialiser les ennemis
    render_map(&game);    // Render the map with textures
    
    mlx_hook(game.win, 17, 0, (int (*)())close_window, &game);
    mlx_key_hook(game.win, handle_key, &game);
    mlx_loop_hook(game.mlx, loop_hook, &game); // Nouvelle fonction pour le rafraîchissement automatique
    mlx_loop(game.mlx);
}