/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 17:28:36 by grohr             #+#    #+#             */
/*   Updated: 2025/03/24 17:46:37 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int loop_hook(t_game *game)
{
    // Vérifier si les ennemis sont en collision avec le joueur
    check_enemy_collision(game);
    
    // Rafraîchir l'affichage
    render_map(game);
    
    // Ajouter un petit délai pour éviter une utilisation excessive du CPU
    usleep(5000); // 50ms
    
    return (0);
}