/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:16:59 by bribot            #+#    #+#             */
/*   Updated: 2026/01/27 17:01:41 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>

void	ft_bzero(void *src, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		((unsigned char *)src)[i] = 0;
		i++;
	}
	return ;
}

/*
#include<stdio.h>
int main(void)
{
	int src[5];
	int i = 0;
	
	ft_bzero(&src, 5);
	while (i < 50)
	{
		printf("%d ", src[i]);
		i++;
	}
}
*/