/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:05:35 by jchartie          #+#    #+#             */
/*   Updated: 2025/11/24 16:17:50 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The  memcpy()  function  copies  n bytes from memory area src to memory
       area dest.  The memory areas must not overlap.
 * @param dst A pointer to the memory location where the copied 
 * data will be stored.
 * @param src A pointer to the memory location from where the 
 * data is to be copied.
 * @param n The number of bytes to be copied.
 * @return void* The memcpy() function returns a pointer to dest.

 */
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dst && !src)
		return (NULL);
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}
/*
int main(void)
{
    char	*src = NULL;
    char	dst[30] = "";
    size_t    n = 3;

   char	*src2 = NULL;
    char	dst2[30] = "";
    
    printf("memcpy: %s\n", (char *)memcpy(dst2, src2, n));

    printf("ft_memcpy: %s\n", (char *)ft_memcpy(dst, src, n));
}*/