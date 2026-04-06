/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:04:58 by bribot            #+#    #+#             */
/*   Updated: 2026/01/27 17:01:41 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	len_dest;
	size_t	len_src;

	j = 0;
	i = 0;
	len_dest = ft_strlen((char *)dest);
	len_src = ft_strlen((char *)src);
	if (len_dest >= size)
		return (len_src + size);
	while (i + 1 < size && dest[i])
		i++;
	while (i + 1 < size && src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (len_dest + len_src);
}

/*
#include <stdio.h>
#include <bsd/string.h>

int main(void)
{
	char    dest[] = "TEST";
	char    src[] = "test";
	size_t  i = 8;
	
	
	i = ft_strlcat(&dest[0], src, i);
	printf("%s \n %zu", dest, i);
	return (0);
}
	*/