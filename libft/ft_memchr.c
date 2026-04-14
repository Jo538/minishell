/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:03:01 by jchartie          #+#    #+#             */
/*   Updated: 2025/11/21 10:40:25 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The  memchr()  function  scans  the  initial n bytes 
 * of the memory area pointed to by s for the first instance 
 * of c.  Both c and the  bytes  of the memory area pointed 
 * to by s are interpreted as unsigned char.
 * @param s A pointer to the block of memory to search in. 
 * (best with strings, char *) as mem functions operate byte 
 * by byte
 * @param c the character to search for
 * @param n The size of the block of memory to search in.
 * @return void* The  memchr()  and memrchr() functions return 
 * a pointer to the matching byte or NULL if the character does 
 * not occur in the given memory area.
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return (&((unsigned char *)s)[i]);
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	int	s[4] = {0, 2, 3, 4};
	int	c = 5;
	size_t	n = 10;

	printf("memchr: %p\n", memchr(s, c, n));
	printf("memchr: %d\n\n", *(int *)memchr(s, c, n));

	rintf("ft_memchr: %p\n", ft_memchr(s, c, n));
	printf("ft_memchr: %d\n\n", *(int *)ft_memchr(s, c, n));
}*/