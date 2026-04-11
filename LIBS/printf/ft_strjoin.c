/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benji <benji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 09:21:11 by bribot            #+#    #+#             */
/*   Updated: 2026/04/10 00:09:16 by benji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*dest;

	if (!s1 && s2)
		return ((char *)s2);
	if (!s2 && s1)
		return ((char *)s1);
	i = ft_strlen(s1) + ft_strlen(s2);
	dest = malloc(sizeof(char) * i + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1))
	{
		dest[i] = s1[i];
		i++;
	}
	while (i < ft_strlen(s1) + ft_strlen(s2))
	{
		dest[i] = s2[i - ft_strlen(s1)];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

// #include<stdio.h>

// int	main(void)
// {
// 	char	*s;

// 	s = ft_strjoin("TEST","");
// 	printf("%s", s);
// 	free(s);
// 	return (0);
// }