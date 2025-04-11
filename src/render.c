/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 01:32:29 by grohr             #+#    #+#             */
/*   Updated: 2025/03/24 17:54:57 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void render_game_over(t_game *game)
{
    mlx_clear_window(game->mlx, game->win);
    mlx_string_put(game->mlx, game->win, WIDTH/2 - 50, HEIGHT/2, 0xFF0000, "GAME OVER!");
    mlx_string_put(game->mlx, game->win, WIDTH/2 - 80, HEIGHT/2 + 20, 0xFFFFFF, "Caught by enemy!");
}

void render_map(t_game *game)
{
    int x;
    int y;
    int i;
    int size = 50; // Taille d'affichage souhaitée
    
    y = 0;
    mlx_clear_window(game->mlx, game->win);
    
    // Si game over, afficher l'écran de fin
    if (game->game_over)
    {
        render_game_over(game);
        return;
    }
    
    // Rendu de la carte
    while (game->map[y])
    {
        x = 0;
        while (game->map[y][x])
        {
            // D'abord, afficher les dalles partout
            mlx_put_image_to_window(game->mlx, game->win, game->dalle_img, x * size, y * size);
            
            // Ensuite, superposer les autres éléments
            if (game->map[y][x] == '1')
                mlx_put_image_to_window(game->mlx, game->win, game->wall_img, x * size, y * size);
            else if (game->map[y][x] == 'C')
                mlx_put_image_to_window(game->mlx, game->win, game->item_img, x * size, y * size);
            else if (game->map[y][x] == 'E')
                mlx_put_image_to_window(game->mlx, game->win, game->exit_img, x * size, y * size);
            x++;
        }
        y++;
    }
    
    // Afficher le joueur à sa position actuelle
    mlx_put_image_to_window(game->mlx, game->win, game->dalle_img, 
                           game->player_x * size, game->player_y * size);
    mlx_put_image_to_window(game->mlx, game->win, game->player_img, 
                           game->player_x * size, game->player_y * size);
    
    // Afficher les ennemis
    for (i = 0; i < game->enemy_count; i++)
    {
        mlx_put_image_to_window(game->mlx, game->win, game->dalle_img, 
                              game->enemies[i].x * size, game->enemies[i].y * size);
        mlx_put_image_to_window(game->mlx, game->win, game->enemy_img, 
                              game->enemies[i].x * size, game->enemies[i].y * size);
    }

    // Déplacer les ennemis après chaque rendu
    move_enemies(game);
    
    // Afficher le compteur de mouvements à l'écran
    char move_count_str[20];
    sprintf(move_count_str, "MOVES: %d", game->move_count);
    mlx_string_put(game->mlx, game->win, 10, 20, 0x000000, move_count_str);
}