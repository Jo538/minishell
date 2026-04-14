/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:10:15 by jchartie          #+#    #+#             */
/*   Updated: 2025/11/21 11:00:59 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The  bzero()  function  erases  the  data  in the n bytes of the memory
       starting at the location pointed to by s, by writing zeros (bytes  con‐
       taining '\0') to that area.
 * 
 * @param s Whatever the pointer s points to, best for char * (strings) as 
 * operates byte per byte.
 * @param n The number of bytes to override to '\0'
 */
void	ft_bzero(void *s, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = '\0';
		i++;
	}
}
/*
int	main(void)
{
	char arr[5] = "test";
	int	n = 2;

	char test[10] = "test\0";
	bzero(test, n);
	printf("%s", test + 2);
	
	ft_bzero(arr, n);
	printf("%s", arr + 2);
}*/