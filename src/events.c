/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:20:15 by grohr             #+#    #+#             */
/*   Updated: 2025/04/16 16:25:04 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
		close_game(game);
	else if (keycode == W_KEY || keycode == U_ARROW)
		move_player(game, game->player_x, game->player_y - 1);
	else if (keycode == A_KEY || keycode == L_ARROW)
		move_player(game, game->player_x - 1, game->player_y);
	else if (keycode == S_KEY || keycode == D_ARROW)
		move_player(game, game->player_x, game->player_y + 1);
	else if (keycode == D_KEY || keycode == R_ARROW)
		move_player(game, game->player_x + 1, game->player_y);
	return (0);
}

int	close_game(t_game *game)
{
	free_game(game);
	exit(0);
	return (0);
}
