/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:17:18 by grohr             #+#    #+#             */
/*   Updated: 2025/04/17 17:52:58 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->map = NULL;
	game->map_width = 0;
	game->map_height = 0;
	game->player_x = 0;
	game->player_y = 0;
	game->collectibles = 0;
	game->collected = 0;
	game->moves = 0;
	game->exit_x = 0;
	game->exit_y = 0;
	game->player_count = 0;
	game->exit_count = 0;
	game->collectible.img = NULL;
	game->exit.img = NULL;
	game->floor.img = NULL;
	game->player.img = NULL;
	game->wall.img = NULL;
}

// Initialise la fenêtre du jeu avec la bonne taille et un titre.
// Retourne 1 si succès, 0 si échec.
//
// mlx_init :
// Initialise la connexion à la MinilibX et au système graphique.
// Renvoie un pointeur vers une structure interne (context graphique).
//
// mlx_new_window :
// Crée une nouvelle fenêtre de dimensions (largeur x hauteur), en pixels.
// - game->map_width * IMG_SIZE : largeur de la fenêtre en pixels
// - game->map_height * IMG_SIZE : hauteur de la fenêtre en pixels
//
// mlx_destroy_display :
// Si la fenêtre n'a pas pu être créée, on détruit le display
// et on libère la mémoire allouée par mlx_init

int	init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = mlx_new_window(game->mlx, game->map_width * IMG_SIZE,
			game->map_height * IMG_SIZE, "So_long_Gauthier");
	if (!game->win)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
		return (0);
	}
	return (1);
}

// Configure les hooks (événements clavier et fermeture fenêtre)
//
// 2 touche pressée : on appelle key_press
// 1L << 0 : masque binaire pour capturer les pressions de touche
// (1L << 1) : touche relachee
//
// 17 : Code de l'événement fermeture de fenêtre (clic sur la croix par ex.)
// 1L << 17 : Fenêtre en train de se fermer

void	setup_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 17, 1L << 17, close_game, game);
}

/*
mlx_init() |

Initialise la connexion au serveur graphique (X11 sous Linux).
Renvoie un pointeur vers une structure gérant tout le contexte MLX.
C'est la première fonction à appeler avant toute autre fonction MLX.

mlx_new_window() |

Crée une nouvelle fenêtre avec une taille en pixels et un titre.
Nécessite le pointeur mlx retourné par mlx_init.
Renvoie un pointeur vers la fenêtre, à utiliser pour les hooks et le rendu.

mlx_destroy_display() | 

Détruit les structures internes liées à la connexion au serveur X11
(libère la mémoire allouée par mlx_init).
Nécessaire pour nettoyer correctement en cas d’erreur ou à la fin du programme.


mlx_hook() |

Attache une fonction callback à un événement de la fenêtre
(ex: touche pressée, souris bougée, fermeture fenêtre, etc.).
On précise :
- window
- l’événement : (ex: 2 pour touche, 17 pour fermeture)
- mask : un filtre binaire qui précise quand l’événement doit être capté
- callback : la fonction à appeler
- param : un pointeur de paramètre utilisateur (généralement game).
*/