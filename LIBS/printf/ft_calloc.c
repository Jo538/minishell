/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:48:35 by bribot            #+#    #+#             */
/*   Updated: 2026/01/27 17:01:41 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>

void	*ft_calloc(size_t size, size_t nbr)
{
	char	*s1;
	size_t	len;
	size_t	i;

	i = 0;
	len = size * nbr;
	if (nbr && (size != (len / nbr)))
		return (NULL);
	s1 = malloc(len);
	if (!s1)
		return (NULL);
	while (i < len)
	{
		s1[i] = 0;
		i++;
	}
	return (s1);
}

// #include <stdio.h>

// int main(void)
// {
// char	*s;

// size_t size = -5;
// size_t nbr = -5;
// s = ft_calloc(size, nbr);
// printf ("%s ", s);
// free (s);
// return (0);
// }