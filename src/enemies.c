/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:30:00 by grohr             #+#    #+#             */
/*   Updated: 2025/03/16 16:25:09 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// Compte le nombre d'ennemis dans la carte
int count_enemies(char **map)
{
    int count;
    int i;
    int j;

    count = 0;
    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'A')
                count++;
            j++;
        }
        i++;
    }
    return (count);
}

// Initialise les ennemis en parcourant la carte
void init_enemies(t_game *game)
{
    int i;
    int j;
    int enemy_index;

    game->enemy_count = count_enemies(game->map);
    if (game->enemy_count == 0)
        return;
    
    game->enemies = (t_enemy *)malloc(sizeof(t_enemy) * game->enemy_count);
    if (!game->enemies)
    {
        ft_printf("Error\nMemory allocation failed for enemies.\n");
        close_window(game);
    }

    enemy_index = 0;
    i = 0;
    while (game->map[i])
    {
        j = 0;
        while (game->map[i][j])
        {
            if (game->map[i][j] == 'A')
            {
                game->enemies[enemy_index].x = j;
                game->enemies[enemy_index].y = i;
                game->enemies[enemy_index].direction = enemy_index % 2; // Alternance horizontal/vertical
                game->enemies[enemy_index].move_counter = 0;
                game->map[i][j] = '0'; // Remplacer par du sol dans la carte
                enemy_index++;
            }
            j++;
        }
        i++;
    }
}

// Déplace les ennemis selon leur direction
void move_enemies(t_game *game)
{
    int i;
    int new_x;
    int new_y;

    if (game->enemy_count == 0 || game->game_over)
        return;

    for (i = 0; i < game->enemy_count; i++)
    {
        // Ralentir le mouvement des ennemis (ils se déplacent tous les 15 rendus)
        game->enemies[i].move_counter++;
        if (game->enemies[i].move_counter < 15)
            continue;
        
        game->enemies[i].move_counter = 0;
        
        // Calculer la nouvelle position
        new_x = game->enemies[i].x;
        new_y = game->enemies[i].y;
        
        if (game->enemies[i].direction == 0) // Horizontal
            new_x += (i % 2 == 0) ? 1 : -1;
        else // Vertical
            new_y += (i % 2 == 0) ? 1 : -1;
        
        // Vérifier si la nouvelle position est valide (pas de mur)
        if (game->map[new_y][new_x] != '1' && game->map[new_y][new_x] != 'E')
        {
            game->enemies[i].x = new_x;
            game->enemies[i].y = new_y;
        }
        else
        {
            // Changer de direction si on rencontre un obstacle
            if (game->enemies[i].direction == 0) // Horizontal
                game->enemies[i].x += (i % 2 == 0) ? -1 : 1;
            else // Vertical
                game->enemies[i].y += (i % 2 == 0) ? -1 : 1;
        }
    }
    
    // Vérifier les collisions avec le joueur après le mouvement
    check_enemy_collision(game);
}

// Vérifie si le joueur est en collision avec un ennemi
void check_enemy_collision(t_game *game)
{
    int i;

    if (game->enemy_count == 0 || game->game_over)
        return;

    for (i = 0; i < game->enemy_count; i++)
    {
        if (game->player_x == game->enemies[i].x && game->player_y == game->enemies[i].y)
        {
            game->game_over = true;
            ft_printf("\n❌ Game Over! You were caught by an enemy! ❌\n");

            // Afficher "Game Over" dans une boucle pour donner le temps au joueur de voir
            render_map(game);
            usleep(2000000); // Attendre 2 secondes
            close_window(game);
        }
    }
}