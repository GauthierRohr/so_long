/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:16:31 by grohr             #+#    #+#             */
/*   Updated: 2025/04/16 15:55:25 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include "../libft.h"

/* # include <stdio.h>
# include <fcntl.h> */

// stddef.h -> for size_t
// unistd.h -> for read(), ssize_t
// fcntl.h  -> for O_RDONLY & open()

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4242
# endif

char	*get_next_line(int fd);
char	*ft_add_line(int fd, char *str);
char	*ft_next_line(char *str);
char	*ft_remove_str_1st_line(char *line);
char	*ft_strjoin_g(char *s1, char *s2);
char	*ft_strchr_g(char *str, int c);
size_t	ft_strlen_g(char *str);
void	free_gnl_static(void);

#endif