/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:58:24 by bribot            #+#    #+#             */
/*   Updated: 2026/01/27 17:01:41 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>

void	*ft_memset(void *src, int value, size_t size)
{
	unsigned long int	i;

	i = 0;
	while (i < size)
	{
		((unsigned char *)src)[i] = value;
		i++;
	}
	return (src);
}

/*
#include<stdio.h>
#include<string.h>

int main(void)
{
	size_t size = 4;
	char src[size + 1];
	unsigned int i = 0;
	memset(&src, '!', size);
	while (i < size)
	{	
		printf("%s \n", &src[i]);
		i++;
	}
	i = 0;
	ft_memset(&src, '!', size);
	while (i < size)
	{	
		printf("\nle mien \n%s", &src[i]);
		i++;
	}
	return (0);
}
*/