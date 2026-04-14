/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:12:25 by jchartie          #+#    #+#             */
/*   Updated: 2025/11/24 12:23:38 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*char	f(unsigned int n, char c)
{
	return (c - n);
}*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	size_t	i;
	char	*dst;

	i = 0;
	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	dst = (char *)malloc((len + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	while (s[i])
	{
		dst[i] = f(i, s[i]);
		i++;
	}
	dst[len] = '\0';
	return (dst);
}
/*
int main(void)
{
	char *s = "";
	char *dst = ft_strmapi(s, f);
	printf("%s\n", dst);
}*/