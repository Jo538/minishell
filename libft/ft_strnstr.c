/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 10:31:08 by jchartie          #+#    #+#             */
/*   Updated: 2025/11/24 16:20:10 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	i = 0;
	if (!needle[0])
		return ((char *)haystack);
	if (len == 0 || !haystack[0])
		return (NULL);
	while (haystack[i] && needle[i] && haystack[i] == needle[i] && i < len)
		i++;
	if (!needle[i])
		return ((char *)haystack);
	return (ft_strnstr(haystack + 1, needle, len - 1));
}
/*
int    main(void)
{
    char *haystack = "";
    char *needle = "coucou";
    size_t len = -1;

    printf("strnstr: %s\n\n", strnstr(haystack, needle, len));
    printf("ft_strnstr: %s\n\n", ft_strnstr(haystack, needle, len));
}*/
