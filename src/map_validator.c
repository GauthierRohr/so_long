/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:19:18 by grohr             #+#    #+#             */
/*   Updated: 2025/04/16 16:42:18 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static int	check_characters(t_game *game, int i, int j, char c)
{
	if (c == 'P')
	{
		game->player_count++;
		game->player_x = j;
		game->player_y = i;
	}
	else if (c == 'E')
	{
		game->exit_count++;
		game->exit_x = j;
		game->exit_y = i;
	}
	else if (c == 'C')
		game->collectibles++;
	else if (c != '0' && c != '1')
		return (0);
	return (1);
}

static int	check_components(t_game *game)
{
	int		i;
	int		j;
	char	c;

	game->player_count = 0;
	game->exit_count = 0;
	game->collectibles = 0;
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			c = game->map[i][j];
			if (!check_characters(game, i, j, c))
				return (0);
			j++;
		}
		i++;
	}
	if (game->player_count != 1 || game->exit_count != 1
		|| game->collectibles < 1)
		return (0);
	return (1);
}

static int	check_walls(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if ((i == 0 || i == game->map_height - 1 || j == 0
					|| j == game->map_width - 1) && game->map[i][j] != '1')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	check_rectangle(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_height)
	{
		if ((int)ft_strlen(game->map[i]) != game->map_width)
			return (0);
		i++;
	}
	return (1);
}

int	validate_map(t_game *game)
{
	if (!check_rectangle(game))
		return (0);
	if (!check_walls(game))
		return (0);
	if (!check_components(game))
		return (0);
	return (1);
}
