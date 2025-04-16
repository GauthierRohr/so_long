/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:17:23 by grohr             #+#    #+#             */
/*   Updated: 2025/04/16 16:05:24 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_g(char *string)
{
	size_t	i;

	i = 0;
	if (!string)
		return (0);
	while (string[i])
		i++;
	return (i);
}

// strchr -> looking for '\n' in the line we want to read.

char	*ft_strchr_g(char *str, int c)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin_g(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*out;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	if (!s2)
		return (NULL);
	out = (char *)malloc(sizeof(char) * (ft_strlen_g(s1) + ft_strlen_g(s2)
				+ 1));
	if (out == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		out[j++] = s1[i++];
	i = 0;
	while (s2[i])
		out[j++] = s2[i++];
	out[j] = '\0';
	free(s1);
	return (out);
}

char	*ft_next_line(char *str)
{
	char	*next;
	int		i;

	i = 0;
	if (str[i] == 0)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	next = malloc(sizeof(char) * (i + 2));
	if (!next)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		next[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		next[i++] = '\n';
	next[i] = '\0';
	return (next);
}

char	*ft_remove_str_1st_line(char *line)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i])
	{
		free(line);
		return (NULL);
	}
	new_str = malloc(sizeof(char) * (ft_strlen_g(line) - i + 1));
	if (!new_str)
		return (free(line), NULL);
	i++;
	while (line[i])
		new_str[j++] = line[i++];
	new_str[j] = '\0';
	free(line);
	return (new_str);
}
