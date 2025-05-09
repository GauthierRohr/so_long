/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:19:32 by grohr             #+#    #+#             */
/*   Updated: 2025/04/17 17:13:13 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	free_copy(char **copy, int height)
{
	int	i;

	if (!copy)
		return ;
	i = 0;
	while (i < height)
	{
		if (copy[i])
			free(copy[i]);
		i++;
	}
	free(copy);
}

// On part de la position du joueur pour le flood fill
// Donc si un collectible ou l'exit ne sont ps remplacees par 'F'
// --> chemin inatteignable
// On quitte alors le programme

static int	check_reachable(char **map, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if ((map[i][j] == 'C') || (map[i][j] == 'E'))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static void	flood_fill(char **map, int x, int y, t_game *game)
{
	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height
		|| map[y][x] == '1' || map[y][x] == 'F')
		return ;
	map[y][x] = 'F';
	flood_fill(map, x + 1, y, game);
	flood_fill(map, x - 1, y, game);
	flood_fill(map, x, y + 1, game);
	flood_fill(map, x, y - 1, game);
}

// free_copy --> free.c
// on copie juste la map pour faire un flood fill et check les paths

char	**copy_map(t_game *game)
{
	char	**copy;
	int		i;

	copy = (char **)malloc(sizeof(char *) * (game->map_height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < game->map_height)
	{
		copy[i] = ft_strdup(game->map[i]);
		if (!copy[i])
		{
			free_copy(copy, i);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int	check_path(t_game *game)
{
	char	**copy;
	int		result;

	copy = copy_map(game);
	if (!copy)
		return (0);
	flood_fill(copy, game->player_x, game->player_y, game);
	result = check_reachable(copy, game);
	free_copy(copy, game->map_height);
	return (result);
}
