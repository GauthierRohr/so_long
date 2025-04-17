/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:58:56 by grohr             #+#    #+#             */
/*   Updated: 2025/04/17 18:09:33 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	render_tile(t_game *game, t_img *img, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, img->img, x * IMG_SIZE,
		y * IMG_SIZE);
}

// Reload seulement une tile
static void	render_single_tile(t_game *game, int x, int y)
{
	render_tile(game, &game->floor, x, y);
	if (game->map[y][x] == '1')
		render_tile(game, &game->wall, x, y);
	else if (game->map[y][x] == 'C')
		render_tile(game, &game->collectible, x, y);
	if (game->map[y][x] == 'E')
		render_tile(game, &game->exit, x, y);
	if (x == game->player_x && y == game->player_y)
		render_tile(game, &game->player, x, y);
}

//afficher le comp
static void	render_moves_counter(t_game *game)
{
	char	*moves_str;
	char	*prefix;
	char	*full_str;

	prefix = "MOVES : ";
	moves_str = ft_itoa(game->moves);
	full_str = ft_strjoin(prefix, moves_str);
	if (!full_str)
		return ;
	mlx_string_put(game->mlx, game->win, 10, 20, 0xFFFFFF, full_str);
	free(moves_str);
	free(full_str);
}

// Rendu initial de TOUTE la carte
void	render_full_game(t_game *game)
{
	int	x;
	int	y;

	mlx_clear_window(game->mlx, game->win);
	y = -1;
	while (++y < game->map_height)
	{
		x = -1;
		while (++x < game->map_width)
			render_single_tile(game, x, y);
	}
	render_moves_counter(game);
}

// actualise la map
void	render_game(t_game *game)
{
	int			x;
	static int	prev_x = -1;
	static int	prev_y = -1;

	if (prev_x == -1 || prev_y == -1)
	{
		render_full_game(game);
		prev_x = game->player_x;
		prev_y = game->player_y;
		return ;
	}
	render_single_tile(game, prev_x, prev_y);
	render_single_tile(game, game->player_x, game->player_y);
	x = 0;
	while (x++ <= 5 && x < game->map_width && 0 <= game->map_height)
		render_single_tile(game, x, 0);
	while (x++ <= 5 && x < game->map_width && 1 <= game->map_height)
		render_single_tile(game, x, 1);
	while (x++ <= 5 && x < game->map_width && 2 <= game->map_height)
		render_single_tile(game, x, 2);
	prev_x = game->player_x;
	prev_y = game->player_y;
	render_moves_counter(game);
}
