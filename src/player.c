/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:20:00 by grohr             #+#    #+#             */
/*   Updated: 2025/04/17 12:03:50 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static void	end_game(t_game *game)
{
	ft_printf("\n\033[32m=== FÉLICITATIONS ! ===\033[0m\n");
	ft_printf("T'as fini le jeu en %d moves!\n", game->moves);
	ft_printf("Les %d collectibles ont été ramassés.\n\n", game->collectibles);
	free_game(game);
	exit(0);
}

static int	handle_exit(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == 'E' && game->collected == game->collectibles)
	{
		end_game(game);
		return (1);
	}
	return (0);
}

static void	update_previous_position(t_game *game)
{
	int	was_on_exit;

	was_on_exit = (game->map[game->player_y][game->player_x] == 'E');
	if (was_on_exit)
		game->map[game->player_y][game->player_x] = 'E';
	else
		game->map[game->player_y][game->player_x] = '0';
}

// print_stats --> dans main
static void	handle_collectible(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == 'C')
	{
		game->map[new_y][new_x] = '0';
		game->collected++;
		print_stats(game);
	}
}

int	move_player(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == '1')
		return (0);
	handle_collectible(game, new_x, new_y);
	update_previous_position(game);
	game->player_x = new_x;
	game->player_y = new_y;
	if (game->map[new_y][new_x] != 'E')
		game->map[new_y][new_x] = 'P';
	if (handle_exit(game, new_x, new_y))
		return (1);
	game->moves++;
	ft_printf("\033[2A");
	ft_printf("\033[2K");
	ft_printf("🍒 Collectible %d/%d\n", game->collected, game->collectibles);
	ft_printf("\033[2K");
	ft_printf("👟 Moves: %d\n", game->moves);
	render_game(game);
	return (1);
}
