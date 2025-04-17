/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:19:18 by grohr             #+#    #+#             */
/*   Updated: 2025/04/17 16:35:59 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

// localise le Player initial + Exit
// compte P, E et C pour check_components
// return si autre char que 0, 1, C, E et P

static int	check_characters(t_game *game, int y, int x, char c)
{
	if (c == 'P')
	{
		game->player_count++;
		game->player_x = x;
		game->player_y = y;
	}
	else if (c == 'E')
	{
		game->exit_count++;
		game->exit_x = x;
		game->exit_y = y;
	}
	else if (c == 'C')
		game->collectibles++;
	else if (c != '0' && c != '1')
		return (0);
	return (1);
}

// initialise les compteurs player, collectible et exit
// on check chaque char de la map avec check_characters
// on quitte si :
//		!= de 1 Player
//		!= de 1 Exit
//		<  de 1 Collectible

static int	check_components(t_game *game)
{
	int		y;
	int		x;
	char	c;

	game->player_count = 0;
	game->exit_count = 0;
	game->collectibles = 0;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			c = game->map[y][x];
			if (!check_characters(game, y, x, c))
				return (0);
			x++;
		}
		y++;
	}
	if (game->player_count != 1
		|| game->exit_count != 1
		|| game->collectibles < 1)
		return (0);
	return (1);
}

// si :
//		1ere ligne (y == 0)
//	ou	derniere ligne (y == game->map_height - 1)
//	ou	1ere colonne (x == 0)
//	ou	derniere colonne (x == game->map_width - 1)
//
//  ET	different de mur (1), alors on quitte

static int	check_walls(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if ((y == 0
					|| y == game->map_height - 1
					|| x == 0
					|| x == game->map_width - 1)
				&& game->map[y][x] != '1')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

// double check car deja fait dans map_reader.c dans process_line
// mais securise

static int	check_rectangle(t_game *game)
{
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		if ((int)ft_strlen(game->map[y]) != game->map_width)
			return (0);
		y++;
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
