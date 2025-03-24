/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:55:39 by grohr             #+#    #+#             */
/*   Updated: 2025/03/16 16:29:41 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int handle_key(int key, t_game *game)
{
    // Ne pas réagir aux touches si le jeu est terminé
    if (game->game_over)
        return (0);
        
    if (key == 53) // ESC key
        close_window(game);
    else if ((key == 13 || key == 126) && game->map[game->player_y - 1][game->player_x] != '1') // W key or Up arrow
    {
        game->player_y--;
        game->move_count++;
    }
    else if ((key == 1 || key == 125) && game->map[game->player_y + 1][game->player_x] != '1') // S key or Down arrow
    {
        game->player_y++;
        game->move_count++;
    }
    else if ((key == 0 || key == 123) && game->map[game->player_y][game->player_x - 1] != '1') // A key or Left arrow
    {
        game->player_x--;
        game->move_count++;
    }
    else if ((key == 2 || key == 124) && game->map[game->player_y][game->player_x + 1] != '1') // D key or Right arrow
    {
        game->player_x++;
        game->move_count++;
    }

    // Afficher le nombre total de mouvements dans le shell
    ft_printf("Total moves: %d\n", game->move_count);
    if (game->map[game->player_y][game->player_x] == 'C')
    {
        game->map[game->player_y][game->player_x] = '0';
        game->collected++;
    }
    if (game->map[game->player_y][game->player_x] == 'E' && game->collected == game->collectibles)
        close_window(game);
    
    // Vérifier si le joueur est en collision avec un ennemi après son déplacement
    check_enemy_collision(game);
    
    render_map(game);
    return (0);
}