/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 01:32:20 by grohr             #+#    #+#             */
/*   Updated: 2025/03/16 16:25:40 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void load_textures(t_game *game)
{
    int size = 50; // Taille d'affichage souhaitée
    
    game->wall_img = mlx_xpm_file_to_image(game->mlx, "textures_pokemon/wall.xpm", &size, &size);
    game->dalle_img = mlx_xpm_file_to_image(game->mlx, "textures_pokemon/dalle.xpm", &size, &size);
    game->player_img = mlx_xpm_file_to_image(game->mlx, "textures_pokemon/player.xpm", &size, &size);
    game->item_img = mlx_xpm_file_to_image(game->mlx, "textures_pokemon/item.xpm", &size, &size);
    game->exit_img = mlx_xpm_file_to_image(game->mlx, "textures_pokemon/exit.xpm", &size, &size);
    game->enemy_img = mlx_xpm_file_to_image(game->mlx, "textures_pokemon/enemy.xpm", &size, &size);
    
    if (!game->wall_img || !game->dalle_img || !game->player_img || 
        !game->item_img || !game->exit_img || !game->enemy_img)
    {
        ft_printf("Error: Failed to load textures.\n");
        exit(1);
    }
}