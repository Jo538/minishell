/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:50:46 by bribot            #+#    #+#             */
/*   Updated: 2026/01/27 17:01:41 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlen_size_t(const char *s1)
{
	size_t	i;

	i = 0;
	while (s1[i])
		i++;
	return (i);
}

char	*ft_strnstr(const char *to_searched, const char *to_find, size_t size)
{
	unsigned long int	i;
	unsigned long int	j;

	j = 0;
	i = 0;
	if (to_find[0] == 0)
		return ((char *)to_searched);
	while (i < size && to_searched[i])
	{
		while (to_searched[i + j] == to_find[j] && to_searched[i + j] && i
			+ j < size)
		{
			if (to_find[j + 1] == 0)
				return (&((char *)to_searched)[i]);
			j++;
		}
		j = 0;
		i++;
	}
	return (NULL);
}

/*
#include <stdio.h>

int	main(void)
{
	printf("%s" ,ft_strnstr("TEste", "TEstee", 3));
	return (0);
}
*/