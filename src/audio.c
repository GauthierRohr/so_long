/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:00:00 by grohr             #+#    #+#             */
/*   Updated: 2025/03/14 14:55:06 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void init_audio(t_game *game)
{
    // Initialiser SDL
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        ft_printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return;
    }
    
    // Initialiser SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        ft_printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return;
    }
    
    // Charger la musique
    game->music = Mix_LoadMUS("mp3/Pokemon_battle.mp3");
    if (!game->music)
    {
        ft_printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
        return;
    }
    
    // Jouer la musique en boucle (-1 = infini)
    if (Mix_PlayMusic(game->music, -1) == -1)
    {
        ft_printf("Failed to play music! SDL_mixer Error: %s\n", Mix_GetError());
    }
}

void cleanup_audio(t_game *game)
{
    // Libérer la musique
    if (game->music)
    {
        Mix_HaltMusic();
        Mix_FreeMusic(game->music);
        game->music = NULL;
    }
    
    // Fermer SDL_mixer et SDL
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
}