/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benji <benji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:33:42 by jchartie          #+#    #+#             */
/*   Updated: 2026/05/08 09:59:13 by benji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates memory (using malloc(3)) and returns a
new string, which is the result of concatenating
string ’s1’ and string ’s2’.
 * 
 * @param s1 The prefix string.
 * @param s2 The suffix string.
 * @return char* The new string.
NULL if the allocation fails.
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*strjoin;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	strjoin = (char *)malloc(len * sizeof(char));
	if (strjoin == NULL)
		return (NULL);
	ft_strlcpy(strjoin, s1, len);
	ft_strlcat(strjoin, s2, len);
	return (strjoin);
}
/*
int	main(void)
{
	char *s1 = "Hello";
	char *s2 = "";

	printf("%s\n", ft_strjoin(s1, s2));
}*/