/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:46:33 by grohr             #+#    #+#             */
/*   Updated: 2025/04/16 16:40:07 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static void	cleanup_images(t_game *game, int index)
{
	if (index >= 1 && game->collectible.img)
	{
		mlx_destroy_image(game->mlx, game->collectible.img);
		game->collectible.img = NULL;
	}
	if (index >= 2 && game->exit.img)
	{
		mlx_destroy_image(game->mlx, game->exit.img);
		game->exit.img = NULL;
	}
	if (index >= 3 && game->floor.img)
	{
		mlx_destroy_image(game->mlx, game->floor.img);
		game->floor.img = NULL;
	}
	if (index >= 4 && game->player.img)
	{
		mlx_destroy_image(game->mlx, game->player.img);
		game->player.img = NULL;
	}
}

static int	load_image(t_game *game, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(game->mlx, path, (int *)&img->width,
			(int *)&img->height);
	if (!img->img)
		return (0);
	return (1);
}

int	init_images(t_game *game)
{
	if (!load_image(game, &game->collectible, "text_dungeon/collectible.xpm"))
		return (0);
	if (!load_image(game, &game->exit, "text_dungeon/exit.xpm"))
	{
		cleanup_images(game, 1);
		return (0);
	}
	if (!load_image(game, &game->floor, "text_dungeon/floor.xpm"))
	{
		cleanup_images(game, 2);
		return (0);
	}
	if (!load_image(game, &game->player, "text_dungeon/player.xpm"))
	{
		cleanup_images(game, 3);
		return (0);
	}
	if (!load_image(game, &game->wall, "text_dungeon/wall.xpm"))
	{
		cleanup_images(game, 4);
		mlx_destroy_image(game->mlx, game->wall.img);
		game->wall.img = NULL;
		return (0);
	}
	return (1);
}
