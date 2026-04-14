/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:03:24 by jchartie          #+#    #+#             */
/*   Updated: 2025/11/18 14:34:14 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The  memcmp()  function compares the first n bytes (each interpreted as
 * unsigned char) of the memory areas s1 and s2.
 * @param s1 Pointer to the memory block to compare against s2 memory block.
 * @param s2 Pointer to the memory block to compare against s1 memory block.
 * @param n Number of bytes to compare starting from the beginning.
 * @return int The memcmp() function returns  an  integer  
 * less  than,  equal  to,  or greater than zero if the first n 
 * bytes of s1 is found, respectively, to be less than, to match,
 * or be greater than the first n bytes of s2.
 * 
 * For a nonzero return value, the sign is determined by the sign
 * of  the difference  between  the  first  pair of bytes 
 * (interpreted as unsigned char) that differ in s1 and s2.
 * 
 * If n is zero, the return value is zero.
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s1_char;
	const unsigned char	*s2_char;
	size_t				i;

	s1_char = (unsigned char *)s1;
	s2_char = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (s1_char[i] != s2_char[i])
			return ((int)s1_char[i] - s2_char[i]);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	char *s1 = "Hello!";
	char *s2 = "Hello!";
	size_t n = 0;

	printf("memcmp: %d\n\n", memcmp(s1, s2, n));

	printf("ft_memcmp: %d\n", ft_memcmp(s1, s2, n));
}*/