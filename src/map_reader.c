/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:17:44 by grohr             #+#    #+#             */
/*   Updated: 2025/04/16 18:28:09 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static int	count_lines(char *filename)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error: Cannot open file %s\n", filename), -1);
	count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

static int	allocate_map(t_game *game, int height)
{
	int	i;

	game->map = (char **)malloc(sizeof(char *) * (height + 1));
	if (!game->map)
		return (ft_printf("Error: Memory allocation failed\n"), 0);
	i = 0;
	while (i <= height)
		game->map[i++] = NULL;
	game->map_height = height;
	return (1);
}

// La ligne courante a été ajoutée à game->map,
// donc on la considère dans le nettoyage.
//
// else if ((int)ft_strlen(trimmed) != game->map_width)
// {
// 	free_map(game);
// 	return (0);
// }
static int	process_line(t_game *game, char *line, int i)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, "\n\r");
	free(line);
	if (!trimmed)
		return (0);
	game->map[i] = trimmed;
	if (i == 0)
		game->map_width = ft_strlen(trimmed);
	else if ((int)ft_strlen(trimmed) != game->map_width)
	{
		free_map(game);
		return (0);
	}
	return (1);
}

static int	read_map_lines(int fd, t_game *game)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!process_line(game, line, i))
		{
			free_gnl_static();
			return (0);
		}
			
		i++;
		line = get_next_line(fd);
	}
	game->map[i] = NULL;
	return (1);
}

int	read_map(char *filename, t_game *game)
{
	int	fd;
	int	height;

	height = count_lines(filename);
	if (height <= 0)
		return (0);
	if (!allocate_map(game, height))
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		free_map(game);
		return (ft_printf("Error: Cannot open file %s\n", filename), 0);
	}
	if (!read_map_lines(fd, game))
	{
		close(fd);
		free_gnl_static();
		return (0);
	}
	close(fd);
	return (1);
}
