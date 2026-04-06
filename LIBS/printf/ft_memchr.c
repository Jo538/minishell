/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:46:52 by bribot            #+#    #+#             */
/*   Updated: 2026/01/27 17:01:41 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memchr(const void *src, int to_find, size_t size)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *)src;
	i = 0;
	while (i < size)
	{
		if (str[i] == (unsigned char)to_find)
			return ((void *)(str + i));
		i++;
	}
	return (NULL);
}

// #include <stdio.h>

// int	main(void)
// {
// 	size_t sze = 100;
// 	char    source[] = "";

// 	printf("%s", (char *)ft_memchr(source, '4', sze));
// 	return (0);
// }