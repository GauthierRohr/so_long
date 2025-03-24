/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rectangular_map.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:15:05 by grohr             #+#    #+#             */
/*   Updated: 2025/03/14 18:26:54 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int rectangular_map(char **map)
{
    size_t	first_line_length;
    int		i;

	if (!map || !map[0])
		return (0);
	first_line_length = ft_strlen(map[0]);
    i = 1;
    while (map[i])
    {
        if (ft_strlen(map[i]) != first_line_length)
        {
            ft_printf("Error\nMap is not rectangular.\n");
            return (0);
        }
        i++;
    }
    return (1); // La carte est rectangulaire
}