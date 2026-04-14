/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 10:27:18 by jchartie          #+#    #+#             */
/*   Updated: 2025/11/19 10:30:35 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*memory;
	size_t	i;

	i = 0;
	if (count != 0 && size > ((size_t) - 1) / count)
		return (NULL);
	memory = malloc(count * size);
	if (memory == NULL)
		return (NULL);
	while (i < count * size)
	{
		((unsigned char *)memory)[i] = 0;
		i++;
	}
	return (memory);
}
/*
int    main(void)
{
    size_t count = 18446744073709551615UL;
    size_t size = 3;

    void res1 = calloc(count, size);
    voidres2 = ft_calloc(count, size);

    printf("calloc: %p\n\n", res1);
    printf("ft_calloc: %p\n\n", res2);

    free (res1);
    free(res2);
}*/