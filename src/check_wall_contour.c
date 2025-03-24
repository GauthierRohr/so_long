/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall_contour.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:22:16 by grohr             #+#    #+#             */
/*   Updated: 2025/03/14 18:23:39 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int wall_contour(char **map)
{
    int height;
    int width;

	if (!map || !map[0])
		return (0);
	height = 0;
	width = ft_strlen(map[0]);
    while (map[height])
        height++;
    // Vérifier la première et la dernière ligne
    for (int x = 0; x < width; x++)
    {
        if (map[0][x] != '1' || map[height - 1][x] != '1')
        {
            ft_printf("Error\nMap is not surrounded by walls.\n");
            return (0);
        }
    }
    // Vérifier la première et la dernière colonne
    for (int y = 0; y < height; y++)
    {
        if (map[y][0] != '1' || map[y][width - 1] != '1')
        {
            ft_printf("Error\nMap is not surrounded by walls.\n");
            return (0);
        }
    }
    return (1); // La carte est entourée de murs
}