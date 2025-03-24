/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 21:01:15 by grohr             #+#    #+#             */
/*   Updated: 2025/03/16 16:27:41 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void free_map(char **map)
{
    int i = 0;
    if (!map)
        return;
    while (map[i])
    {
        free(map[i]);
        i++;
    }
    free(map);
}

// Function to check if the map has all required elements
// Function to check if the map has all required elements
int check_map_elements(char **map, t_game *game)
{
    int i = 0;
    int j;
    int exit_count = 0;
    int player_count = 0;
    
    game->collectibles = 0;
    game->player_x = -1;
    game->player_y = -1;
    
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'C')
                game->collectibles++;
            else if (map[i][j] == 'P')
            {
                game->player_x = j;
                game->player_y = i;
                player_count++;
            }
            else if (map[i][j] == 'E')
                exit_count++;
            else if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'A')
            {
                ft_printf("Error\nInvalid character in map: %c\n", map[i][j]);
                return (0);
            }
            j++;
        }
        i++;
    }
    if (player_count != 1)
    {
        ft_printf("Error\nMap must contain exactly one player (P).\n");
        return (0);
    }
    if (exit_count != 1)
    {
        ft_printf("Error\nMap must contain exactly one exit (E).\n");
        return (0);
    }
    if (game->collectibles < 1)
    {
        ft_printf("Error\nMap must contain at least one collectible (C).\n");
        return (0);
    }
    
    return (1);
}

char **parse_map(char *file, t_game *game)
{
    char **map;
    int fd;
    int i;
    char *line;
    char *trimmed_line;

    fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        ft_printf("Error\nFailed to open map file.\n");
        return (NULL);
    }

    map = malloc(sizeof(char *) * 1000); // Adjust size as needed
    if (!map)
    {
        ft_printf("Error\nMemory allocation failed.\n");
        close(fd);
        return (NULL);
    }

    i = 0;
    while ((line = get_next_line(fd)))
    {
        trimmed_line = ft_strtrim(line, "\n");
        free(line); // Free original line

        map[i] = trimmed_line;
        i++;
    }
    map[i] = NULL;
    close(fd);

    // Check for empty map
    if (i == 0)
    {
        ft_printf("Error\nMap is empty.\n");
        free_map(map);
        return (NULL);
    }

    // Check all required elements
    if (!check_map_elements(map, game))
    {
        free_map(map);
        return (NULL);
    }

    // Map structure validation
    if (!rectangular_map(map))
    {
        free_map(map);
        return (NULL);
    }

    if (!wall_contour(map))
    {
        free_map(map);
        return (NULL);
    }

    // Create a copy of the map for path validation
    char **map_copy = copy_map(map);
    if (!map_copy)
    {
        ft_printf("Error\nMemory allocation failed during path validation.\n");
        free_map(map);
        return (NULL);
    }

    // Validate path
    if (!valid_path(game, map_copy))
    {
        free_map(map);
        free_map(map_copy);
        return (NULL);
    }
    free_map(map_copy);

    // Replace 'P' with '0' after validation
    map[game->player_y][game->player_x] = '0';

    return (map);
}