/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:19:48 by grohr             #+#    #+#             */
/*   Updated: 2025/04/16 16:08:09 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	render_tile(t_game *game, t_img *img, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, img->img, x * IMG_SIZE,
		y * IMG_SIZE);
}

static void	render_elements(t_game *game, int x, int y)
{
	if (game->map[y][x] == '1')
		render_tile(game, &game->wall, x, y);
	else if (game->map[y][x] == 'C')
		render_tile(game, &game->collectible, x, y);
	if (game->map[y][x] == 'E' && !(x == game->player_x && y == game->player_y))
		render_tile(game, &game->exit, x, y);
	if (x == game->player_x && y == game->player_y)
		render_tile(game, &game->player, x, y);
}

static void	render_moves_counter(t_game *game)
{
	char	*moves_str;
	char	*prefix;
	char	*full_str;

	prefix = "Moves: ";
	moves_str = ft_itoa(game->moves);
	full_str = ft_strjoin(prefix, moves_str);
	if (!full_str)
		return ;
	mlx_string_put(game->mlx, game->win, 10, 20, 0xFFFFFF, full_str);
	free(moves_str);
	free(full_str);
}

void	render_game(t_game *game)
{
	int	x;
	int	y;

	mlx_clear_window(game->mlx, game->win);
	y = -1;
	while (++y < game->map_height)
	{
		x = -1;
		while (++x < game->map_width)
		{
			render_tile(game, &game->floor, x, y);
			render_elements(game, x, y);
		}
	}
	render_moves_counter(game);
}
