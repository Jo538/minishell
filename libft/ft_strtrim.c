/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:35:23 by jchartie          #+#    #+#             */
/*   Updated: 2025/11/21 11:23:37 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_start(char const *s1, char const *set)
{
	size_t	start;

		start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	return (start);
}

static size_t	ft_end(char const *s1, char const *set, size_t start)
{
	size_t	end;

	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	return (end);
}

/**
 * @brief Allocates a new memory string (using malloc). Returns a
copy of string ’s1’ with ANY character present in string ’set’ removed
from the beginning and the end of 's1'.
 * 
 * @param s1 The string to be trimmed.
 * @param set The string containing the SET of characters
 * to be removed. Careful: even if set is represented as a 
 * string, we're looking for individual matches of 
 * CHARACTERS, NOT a WORD.
 * @return char* The trimmed string.
 * NULL if the allocation fails.
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	len;
	char	*dst;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	start = 0;
	start = ft_start(s1, set);
	len = ft_end(s1, set, start) - start;
	dst = (char *)malloc(len + 1);
	if (!dst)
		return (NULL);
	if (len > 0)
	{
		while (i < len)
		{
			dst[i] = s1[start + i];
			i++;
		}
	}
	dst[len] = '\0';
	return (dst);
}
/*
int main(void)
{
	char *s1 = "abcaaa";
	char *set = "ab";
	printf("%s\n", ft_strtrim(s1, set));
}*/