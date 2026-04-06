/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 08:24:53 by bribot            #+#    #+#             */
/*   Updated: 2026/01/27 17:01:41 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include<stdio.h>

static size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static size_t	to_malloc(size_t start, size_t len, const char *s)
{
	if (ft_strlen(s) == 0 || ft_strlen(s) < start)
		return (0);
	if ((ft_strlen(s) - start) < len)
		return (ft_strlen(s) - start);
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	j;

	j = 0;
	len = to_malloc(start, len, s);
	dest = malloc(len + 1);
	if (!dest)
		return (NULL);
	dest[to_malloc(start, len, s)] = '\0';
	while (j < len)
	{
		dest[j] = s[j + start];
		j++;
	}
	return (dest);
}

// int	main(void)
// {
// 	char	*S1;
// 	S1 = ft_substr("hola", 2, 2);
// 	printf("%s", S1);
// 	free (S1);
// 	return (0);
// }