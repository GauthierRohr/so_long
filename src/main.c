/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:17:03 by grohr             #+#    #+#             */
/*   Updated: 2025/04/17 18:08:08 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	print_stats(t_game *game)
{
	ft_printf("\033[2A");
	ft_printf("\033[2K");
	ft_printf("🍒 Collectible %d/%d\n", game->collected, game->collectibles);
	ft_printf("\033[2K");
	ft_printf("👟 Moves: %d\n", game->moves);
}

static int	check_file_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	if (filename[len - 4] != '.' || filename[len - 3] != 'b'
		|| filename[len - 2] != 'e' || filename[len - 1] != 'r')
		return (0);
	return (1);
}

static void	handle_error(t_game *game, char *message)
{
	if (game)
		free_game(game);
	exit_error(message);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		handle_error(NULL, "Error\nUsage: ./so_long map.ber");
	if (!check_file_extension(argv[1]))
		handle_error(NULL, "Error\nMap must have .ber extension : <map>.ber");
	init_game(&game);
	if (!read_map(argv[1], &game))
		handle_error(&game, "Error\nFailed to read map");
	if (!validate_map(&game))
		handle_error(&game, "Error\nInvalid components or structure");
	if (!check_path(&game))
		handle_error(&game, "Error\nNo valid path");
	if (!init_window(&game))
		handle_error(&game, "Error\nFailed to initialize window");
	if (!init_images(&game))
		handle_error(&game, "Error\nFailed to initialize images");
	render_game(&game);
	ft_printf("\n\n\n");
	setup_hooks(&game);
	mlx_loop(game.mlx);
	return (0);
}
