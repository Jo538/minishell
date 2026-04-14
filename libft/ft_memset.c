/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:03:16 by jchartie          #+#    #+#             */
/*   Updated: 2025/11/18 14:40:15 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The  memset()  function  fills  the  first  n  bytes of the memory area
       pointed to by s with the constant byte c.
 * @param s This is a pointer to the block of memory to fill.
 * @param c This is a second parameter of type integer and converts it to an 
 * unsigned char before using it to fill a block of memory.
 * @param n This is the number of bytes to be set to the value.
 * @return void*  The memset() function returns a pointer to the memory area s.
 */
void	*ft_memset(void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	u;

	i = 0;
	u = (unsigned char)c;
	while (i < n)
	{
		((unsigned char *)s)[i] = u;
		i++;
	}
	return (s);
}
/*
int	main(void)
{
	int		i;

	i = 0;
	int	str[5] = {1, 2, 3, 4, 5};
	int	str2[5] = {1, 2, 3, 4, 5};
	memset(str2, 0, 2 * sizeof(int));
	while (i < 5)
	{
		printf("%d ", str2[i]);
		i++;
	}
	printf("%c", '\n');
	i = 0;
	ft_memset(str, 0, 2 * sizeof(int));
	while (i < 5)
	{
		printf("%d ", str[i]);
		i++;
	}
}*/
