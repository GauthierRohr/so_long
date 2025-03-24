/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:04:18 by grohr             #+#    #+#             */
/*   Updated: 2024/10/08 10:17:09 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*table;
	size_t	tot_size;
	size_t	i;

	if (count == 0 || size == 0)
		return (malloc(0));
	tot_size = count * size;
	table = malloc(tot_size);
	if (!table)
		return (NULL);
	i = 0;
	while (i < tot_size)
	{
		((unsigned char *)table)[i] = 0;
		i++;
	}
	return (table);
}

/* #include <stdio.h>

int main()
{
    size_t	count = 5;
    size_t	size = sizeof(int);
	int	*arr;
	size_t	i;

	arr = (int *)ft_calloc(count, size);
    if (arr == NULL)
    {
        printf("Error\n");
        return (1);
    }
	i = 0;
	while (i < count)
	{
        printf("arr[%zu] = %d\n", i, arr[i]);
		i++;
    }
    free(arr);
    return (0);
} */