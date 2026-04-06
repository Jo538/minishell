/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 09:37:20 by bribot            #+#    #+#             */
/*   Updated: 2026/01/27 17:01:41 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_isin(char s, const char *set)
{
	int	j;

	j = 0;
	while (j < ft_strlen(set))
	{
		if (set[j] == s)
			return (1);
		j++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		i;
	size_t		j;
	char		*dest;

	i = 0;
	j = ft_strlen(s1);
	while (ft_isin(s1[i], set))
		i++;
	while (ft_isin(s1[j - 1], set) && j > i)
		j--;
	dest = ft_substr(s1, i, j - i);
	return (dest);
}

/*
#include <stdio.h>
int	main(void)
{
	char	*s;

	s = ft_strtrim("TESTtest12301234", "S04");
	printf("%s", s);
	free(s);
	return(0);
}
*/