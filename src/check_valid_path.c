/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:53:48 by grohr             #+#    #+#             */
/*   Updated: 2025/03/16 16:11:39 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// Function to get the height of the map
size_t get_map_height(char **map)
{
    size_t height;

    height = 0;
    while (map[height])
        height++;
    return (height);
}

// Function to create a copy of the map
char **copy_map(char **map)
{
    char **copy;
    int i;
    int height;

    if (!map)
        return (NULL);
    
    height = 0;
    while (map[height])
        height++;
    
    copy = (char **)malloc(sizeof(char *) * (height + 1));
    if (!copy)
        return (NULL);
    
    i = 0;
    while (i < height)
    {
        copy[i] = ft_strdup(map[i]);
        if (!copy[i])
        {
            while (--i >= 0)
                free(copy[i]);
            free(copy);
            return (NULL);
        }
        i++;
    }
    copy[height] = NULL;
    return (copy);
}

// Recursive function for flood fill
void flood_fill(char **map, int x, int y, t_valid_path *path_data)
{
    // If out of bounds, wall or already visited
    if (y < 0 || x < 0 || y >= (int)get_map_height(map) || x >= (int)ft_strlen(map[y]) || 
        map[y][x] == '1' || map[y][x] == 'V')
        return;

    // If collectible, increment counter
    if (map[y][x] == 'C')
        path_data->collectibles_found++;
    // If exit, mark as found
    else if (map[y][x] == 'E')
        path_data->exit_found = 1;

    // Mark the cell as visited
    map[y][x] = 'V';

    // Explore 4 directions
    flood_fill(map, x + 1, y, path_data); // Right
    flood_fill(map, x - 1, y, path_data); // Left
    flood_fill(map, x, y + 1, path_data); // Down
    flood_fill(map, x, y - 1, path_data); // Up
}

// Main function to check if the path is valid - now accepts the map_copy as parameter
int valid_path(t_game *game, char **map_copy)
{
    t_valid_path path_data;

    // Initialize counters
    path_data.collectibles_found = 0;
    path_data.exit_found = 0;

    // Apply flood fill from player position
    flood_fill(map_copy, game->player_x, game->player_y, &path_data);

    // Check if all collectibles are accessible and if exit is accessible
    if (path_data.collectibles_found != game->collectibles || !path_data.exit_found)
    {
        ft_printf("Error\nInvalid path: ");
        if (path_data.collectibles_found != game->collectibles)
            ft_printf("not all collectibles are reachable.\n");
        else
            ft_printf("exit is not reachable.\n");
        return (0);
    }
    
    return (1);
}